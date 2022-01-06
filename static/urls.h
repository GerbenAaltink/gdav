#include "index_html.h"
#include "vuetify_js.h"
#include "materialdesignicons_css_map.h"
#include "vuetify_js_map.h"
#include "webdav_js.h"
#include "materialdesignicons_min_css.h"
#include "roboto_100_300_400_500_700_900_css.h"
#include "vuetify_min_css.h"
#include "vue_js.h"
#include "main_css.h"

const char * gdav_static_urls[] = {
  "/$gdav/static/index.html",
  "/$gdav/static/vuetify.js",
  "/$gdav/static/materialdesignicons.css.map",
  "/$gdav/static/vuetify.js.map",
  "/$gdav/static/webdav.js",
  "/$gdav/static/materialdesignicons.min.css",
  "/$gdav/static/roboto_100_300_400_500_700_900.css",
  "/$gdav/static/vuetify.min.css",
  "/$gdav/static/vue.js",
  "/$gdav/static/main.css"
};
const unsigned char * gdav_static_blobs[] = {index_html,
  vuetify_js,
  materialdesignicons_css_map,
  vuetify_js_map,
  webdav_js,
  materialdesignicons_min_css,
  roboto_100_300_400_500_700_900_css,
  vuetify_min_css,
  vue_js,
  main_css};
const int gdav_static_urls_count = 10;
