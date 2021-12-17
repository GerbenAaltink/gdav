
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
			method: 'PROPFIND' }).then(async(response)=>{                                                      const body = await response.text();
				const parser = new window.DOMParser().parseFromString(body, "text/xml");  
			let result = {items: [], count:0};
			parser.querySelectorAll('response').forEach((el)=>{
				let item = {};
				item['href'] = el.querySelector('href').innerHTML;
				el.querySelector('prop').querySelectorAll("*").forEach(prop=>{
					 item[prop.localName] = prop.innerHTML;
				});
                console.info(item);
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
            result.items.forEach(async(item)=>{
                if(item.iscollection == "1"){
                    item["items"] = await this.propfindRecursive(item['href'], depth - 1);
                }
            });
        }
		return result;;
	}
}

const davClient = new WebDav();
