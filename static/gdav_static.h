#include "index_html.h"
#include "materialdesignicons_min_css.h"
#include "roboto_100_300_400_500_700_900_css.h"
#include "vuetify_js.h"
#include "vuetify_min_css.h"

const char* gdav_static_urls[] = {
    "/$gdav/static/index.html",
    "/$gdav/static/vuetify.js",
    "/$gdav/static/materialdesignicons.min.css",
    "/$gdav/static/roboto_100_300_400_500_700_900.css",
    "/$gdav/static/vuetify.min.css"
};
const unsigned char* gdav_static_blobs[] = { index_html,
    vuetify_js,
    materialdesignicons_min_css,
    roboto_100_300_400_500_700_900_css,
    vuetify_min_css };
const gdav_static_urls_count = 5;
