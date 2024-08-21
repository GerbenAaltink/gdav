
class WebDav {
	head(url) {
		return fetch(url, {
			method: 'HEAD'
		}).then((response)=>{
			console.info(response.headers['Content-Length']);
		});
	}
	propfind(url) {
		return fetch(url, {
			method: 'PROPFIND' }).then(async(response)=>{                                                      
				const body = await response.text();
				console.info(body)
				const parser = new window.DOMParser().parseFromString(body, "text/xml");  
			let result = {items: [], count:0};
			parser.querySelectorAll('response').forEach((el)=>{
				let item = {};
				item['href'] = el.querySelector('href').innerHTML;
				
				el.querySelector('prop').querySelectorAll("*").forEach(prop=>{
					 item[prop.localName] = prop.innerHTML;
				});
				if(item['href'] != url)
				result.items.push(item);
			});
			result.count = result.items.length;
			return result;
		});		
	}
	async propfindRecursive(url, depth) {
		if(depth == undefined)
			depth = 5;
		let result = await this.propfind(url);
        if(depth) {
            result.items.filter(item=>item.href!=url).forEach(async(item)=>{
                
				if(item['href'] != url && item.iscollection == "1"){
					
                    item["items"] = await this.propfindRecursive(item['href'], depth - 1);
                }
            });
        }
		return result.items
	}
}

const davClient = new WebDav();

Vue.component('davplayer', {
	name: 'davplayer',
	template: `<v-card>
		<video autoplay controls style="width: 100%; height:100%;">
			<source :src="path" type="video/mp4" >
		</video>
		</v-card>`,
	props: ['path'],
	data() {
		return {
			currentPath: this.$props['path']
		}
	},
	listeners: {
		path(val) {
			//this.visible = true;
		}
	}
})
// KIM: https://codepen.io/miyukki/pen/dPXeKG
Vue.component('davfilelist', {
	name: 'davfilelist',
	template: `<v-card :loading="loading">

		<v-card>
			<v-card-subtitle>
		<b>{{currentPath}}</b></v-card-subtitle>
		
			<v-card-actions>
				<v-btn small plain @click="onClick(upItem)">..</v-btn>
			<v-btn small plain type="link" @click="loadData()">Refresh</v-btn>
			<v-btn v-if="false" @click="onSearch('mp4');">Video</v-btn>
			</v-card-actions>
		</v-card>
		<davplayer v-if="playerEnabled" :path="playerHref" :v-on:close="()=>{playerEnabled = false;}" />
		<v-card @click="onClick(item)" v-for="item in items" :key="item.displayname" v-if="item.displayname != ''">
			<v-card-actions>
				
			</v-card-actions>
			<v-card-title>{{item.displayname}}</v-card-title>
			<v-card-subtitle>{{ formatSize(item) }} {{ item.getcontenttype }}</v-card-subtitle>
			
		</v-card>
	</v-card>`,
	data() {
		return {
			currentPath: this.$props['path'],
			sortBy: 'displayname',
			items: [],
			upItem: {},
			playerHref: null,
			playerEnabled: false,
			loading: false
		}
	},
	props: ['path'],
	methods: {
        isVideo(item){
            return item['href'].endsWith(".mp4") || item['href'].endsWith(".avi") || item['href'].endsWith(".mkv");
        },
        playVideo(item){
            this.playerHref = item['href'];
			this.playerEnabled = true;
        },
        hideVideo(){
            this.playerEnabled = false;
        },
        navigate(item){
            this.currentPath = item['href'];
            this.loadData();
        },
		onClick(item){
            this.hideVideo();
			if(this.isVideo(item))
            {
			    this.playVideo(item);
            }else if(item['iscollection'] == "1")
			{
			    this.navigate(item);
            }
		},
		async onSearch(what) {
			this.loading = true;
			what = what.toLowerCase();
			let result = await davClient.propfindRecursive(this.$data['currentPath'],2);
			let items = [];
			
			const filterItems = (match, items)=>{
				let res = [];
				items.forEach((item)=>{
					if(item.displayname.indexOf(match) != -1)
						res.push(item);
					if(item['items'])
						filterItems(match, item['items']).forEach(e=>res.push)
				})
				return res;
			}

			this.$data['items'] = filterItems(what, result)
			this.sortData(this.$data['sortBy']);

			this.sortData("-iscollection");
			this.$data['loading'] = false;
		},
		async loadData() {
			this.setUpItem();
			this.loading = true;
			let result = await davClient.propfind(this.$data['currentPath']);
			this.items = result.items;
			this.sortData(this.$data['sortBy']);
			this.sortData("-iscollection");

			this.loading = false;
		},
		setUpItem() {
			let newPath = this['currentPath'].substr(0,this['currentPath'].lastIndexOf("/"));
            if(newPath == '')
                newPath = '/';
			this.upItem = {
			    displayname: "..",
			    href: newPath,
			    iscollection: "1"
			};
		},
		formatSize(item) {
			if(item.iscollection == "1")
				return "[DIR]";
			let size = item.getcontentlength;
			if(size > 1024 * 1024 * 1024){
				return (size / (1024 * 1024 * 1024)).toFixed(2).toString() + " Gb";
			}
			if(size > 1024 * 1024){
				return (size / (1024 * 1024)).toFixed(2).toString() + " Mb";
			}
			if(size > 1024){
				return (size / 1024).toFixed(2).toString() + " Kb";
			}
		    return (size).toString() + " B";
			
		},
		sortData(field) {
			const descending = field.substr(0, 1) == '-';
			let positive = 1;
			let negative = -1;

			if(descending)
			{
				field = field.substr(1);
				negative = 1;
				positive = -1;
			}
			this.items.sort((a, b)=>{
				if(a[field] > b[field]){
					return positive;
				}else if(a[field] < b[field]){
					return negative;
				}else{
					return 0;
				}
			})
		}
	},
	async created() {
		await this.loadData();
		window.DavFileList = this;
	}

});
