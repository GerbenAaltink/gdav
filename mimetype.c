//Author:	Gerben Aaltink
//Last Modified:	Dec  8 2021 17:41:54

#include <stdio.h>
#include <string.h>

const char* get_mimetype(char* name)
{
    char* suffix = strrchr(name, '.');
    if (!suffix)
        return "application/binary";
    if (!strcasecmp(suffix, ".ez"))
        return "application/andrew-inset";
    if (!strcasecmp(suffix, ".anx"))
        return "application/annodex";
    if (!strcasecmp(suffix, ".atom"))
        return "application/atom+xml";
    if (!strcasecmp(suffix, ".atomcat"))
        return "application/atomcat+xml";
    if (!strcasecmp(suffix, ".atomsrv"))
        return "application/atomserv+xml";
    if (!strcasecmp(suffix, ".lin"))
        return "application/bbolin";
    if (!strcasecmp(suffix, ".cu"))
        return "application/cu-seeme";
    if (!strcasecmp(suffix, ".davmount"))
        return "application/davmount+xml";
    if (!strcasecmp(suffix, ".dcm"))
        return "application/dicom";
    if (!strcasecmp(suffix, ".tsp"))
        return "application/dsptype";
    if (!strcasecmp(suffix, ".es"))
        return "application/ecmascript";
    if (!strcasecmp(suffix, ".epub"))
        return "application/epub+zip";
    if (!strcasecmp(suffix, ".otf"))
        return "application/font-sfnt";
    if (!strcasecmp(suffix, ".ttf"))
        return "application/font-sfnt";
    if (!strcasecmp(suffix, ".pfr"))
        return "application/font-tdpfr";
    if (!strcasecmp(suffix, ".woff"))
        return "application/font-woff";
    if (!strcasecmp(suffix, ".spl"))
        return "application/futuresplash";
    if (!strcasecmp(suffix, ".gz"))
        return "application/gzip";
    if (!strcasecmp(suffix, ".hta"))
        return "application/hta";
    if (!strcasecmp(suffix, ".jar"))
        return "application/java-archive";
    if (!strcasecmp(suffix, ".ser"))
        return "application/java-serialized-object";
    if (!strcasecmp(suffix, ".class"))
        return "application/java-vm";
    if (!strcasecmp(suffix, ".js"))
        return "application/javascript";
    if (!strcasecmp(suffix, ".mjs"))
        return "application/javascript";
    if (!strcasecmp(suffix, ".json"))
        return "application/json";
    if (!strcasecmp(suffix, ".jsonld"))
        return "application/ld+json";
    if (!strcasecmp(suffix, ".m3g"))
        return "application/m3g";
    if (!strcasecmp(suffix, ".hqx"))
        return "application/mac-binhex40";
    if (!strcasecmp(suffix, ".cpt"))
        return "application/mac-compactpro";
    if (!strcasecmp(suffix, ".nb"))
        return "application/mathematica";
    if (!strcasecmp(suffix, ".nbp"))
        return "application/mathematica";
    if (!strcasecmp(suffix, ".mbox"))
        return "application/mbox";
    if (!strcasecmp(suffix, ".mdb"))
        return "application/msaccess";
    if (!strcasecmp(suffix, ".doc"))
        return "application/msword";
    if (!strcasecmp(suffix, ".dot"))
        return "application/msword";
    if (!strcasecmp(suffix, ".mxf"))
        return "application/mxf";
    if (!strcasecmp(suffix, ".bin"))
        return "application/octet-stream";
    if (!strcasecmp(suffix, ".deploy"))
        return "application/octet-stream";
    if (!strcasecmp(suffix, ".msu"))
        return "application/octet-stream";
    if (!strcasecmp(suffix, ".msp"))
        return "application/octet-stream";
    if (!strcasecmp(suffix, ".oda"))
        return "application/oda";
    if (!strcasecmp(suffix, ".opf"))
        return "application/oebps-package+xml";
    if (!strcasecmp(suffix, ".ogx"))
        return "application/ogg";
    if (!strcasecmp(suffix, ".one"))
        return "application/onenote";
    if (!strcasecmp(suffix, ".onetoc2"))
        return "application/onenote";
    if (!strcasecmp(suffix, ".onetmp"))
        return "application/onenote";
    if (!strcasecmp(suffix, ".onepkg"))
        return "application/onenote";
    if (!strcasecmp(suffix, ".pdf"))
        return "application/pdf";
    if (!strcasecmp(suffix, ".pgp"))
        return "application/pgp-encrypted";
    if (!strcasecmp(suffix, ".key"))
        return "application/pgp-keys";
    if (!strcasecmp(suffix, ".sig"))
        return "application/pgp-signature";
    if (!strcasecmp(suffix, ".prf"))
        return "application/pics-rules";
    if (!strcasecmp(suffix, ".ps"))
        return "application/postscript";
    if (!strcasecmp(suffix, ".ai"))
        return "application/postscript";
    if (!strcasecmp(suffix, ".eps"))
        return "application/postscript";
    if (!strcasecmp(suffix, ".epsi"))
        return "application/postscript";
    if (!strcasecmp(suffix, ".epsf"))
        return "application/postscript";
    if (!strcasecmp(suffix, ".eps2"))
        return "application/postscript";
    if (!strcasecmp(suffix, ".eps3"))
        return "application/postscript";
    if (!strcasecmp(suffix, ".rar"))
        return "application/rar";
    if (!strcasecmp(suffix, ".rdf"))
        return "application/rdf+xml";
    if (!strcasecmp(suffix, ".rtf"))
        return "application/rtf";
    if (!strcasecmp(suffix, ".stl"))
        return "application/sla";
    if (!strcasecmp(suffix, ".smi"))
        return "application/smil+xml";
    if (!strcasecmp(suffix, ".smil"))
        return "application/smil+xml";
    if (!strcasecmp(suffix, ".xhtml"))
        return "application/xhtml+xml";
    if (!strcasecmp(suffix, ".xht"))
        return "application/xhtml+xml";
    if (!strcasecmp(suffix, ".xml"))
        return "application/xml";
    if (!strcasecmp(suffix, ".xsd"))
        return "application/xml";
    if (!strcasecmp(suffix, ".xsl"))
        return "application/xslt+xml";
    if (!strcasecmp(suffix, ".xslt"))
        return "application/xslt+xml";
    if (!strcasecmp(suffix, ".xspf"))
        return "application/xspf+xml";
    if (!strcasecmp(suffix, ".zip"))
        return "application/zip";
    if (!strcasecmp(suffix, ".apk"))
        return "application/vnd.android.package-archive";
    if (!strcasecmp(suffix, ".cdy"))
        return "application/vnd.cinderella";
    if (!strcasecmp(suffix, ".deb"))
        return "application/vnd.debian.binary-package";
    if (!strcasecmp(suffix, ".ddeb"))
        return "application/vnd.debian.binary-package";
    if (!strcasecmp(suffix, ".udeb"))
        return "application/vnd.debian.binary-package";
    if (!strcasecmp(suffix, ".sfd"))
        return "application/vnd.font-fontforge-sfd";
    if (!strcasecmp(suffix, ".kml"))
        return "application/vnd.google-earth.kml+xml";
    if (!strcasecmp(suffix, ".kmz"))
        return "application/vnd.google-earth.kmz";
    if (!strcasecmp(suffix, ".xul"))
        return "application/vnd.mozilla.xul+xml";
    if (!strcasecmp(suffix, ".xls"))
        return "application/vnd.ms-excel";
    if (!strcasecmp(suffix, ".xlb"))
        return "application/vnd.ms-excel";
    if (!strcasecmp(suffix, ".xlt"))
        return "application/vnd.ms-excel";
    if (!strcasecmp(suffix, ".xlam"))
        return "application/vnd.ms-excel.addin.macroEnabled.12";
    if (!strcasecmp(suffix, ".xlsb"))
        return "application/vnd.ms-excel.sheet.binary.macroEnabled.12";
    if (!strcasecmp(suffix, ".xlsm"))
        return "application/vnd.ms-excel.sheet.macroEnabled.12";
    if (!strcasecmp(suffix, ".xltm"))
        return "application/vnd.ms-excel.template.macroEnabled.12";
    if (!strcasecmp(suffix, ".eot"))
        return "application/vnd.ms-fontobject";
    if (!strcasecmp(suffix, ".thmx"))
        return "application/vnd.ms-officetheme";
    if (!strcasecmp(suffix, ".cat"))
        return "application/vnd.ms-pki.seccat";
    if (!strcasecmp(suffix, ".ppt"))
        return "application/vnd.ms-powerpoint";
    if (!strcasecmp(suffix, ".pps"))
        return "application/vnd.ms-powerpoint";
    if (!strcasecmp(suffix, ".ppam"))
        return "application/vnd.ms-powerpoint.addin.macroEnabled.12";
    if (!strcasecmp(suffix, ".pptm"))
        return "application/vnd.ms-powerpoint.presentation.macroEnabled.12";
    if (!strcasecmp(suffix, ".sldm"))
        return "application/vnd.ms-powerpoint.slide.macroEnabled.12";
    if (!strcasecmp(suffix, ".ppsm"))
        return "application/vnd.ms-powerpoint.slideshow.macroEnabled.12";
    if (!strcasecmp(suffix, ".potm"))
        return "application/vnd.ms-powerpoint.template.macroEnabled.12";
    if (!strcasecmp(suffix, ".docm"))
        return "application/vnd.ms-word.document.macroEnabled.12";
    if (!strcasecmp(suffix, ".dotm"))
        return "application/vnd.ms-word.template.macroEnabled.12";
    if (!strcasecmp(suffix, ".odc"))
        return "application/vnd.oasis.opendocument.chart";
    if (!strcasecmp(suffix, ".odb"))
        return "application/vnd.oasis.opendocument.database";
    if (!strcasecmp(suffix, ".odf"))
        return "application/vnd.oasis.opendocument.formula";
    if (!strcasecmp(suffix, ".odg"))
        return "application/vnd.oasis.opendocument.graphics";
    if (!strcasecmp(suffix, ".otg"))
        return "application/vnd.oasis.opendocument.graphics-template";
    if (!strcasecmp(suffix, ".odi"))
        return "application/vnd.oasis.opendocument.image";
    if (!strcasecmp(suffix, ".odp"))
        return "application/vnd.oasis.opendocument.presentation";
    if (!strcasecmp(suffix, ".otp"))
        return "application/vnd.oasis.opendocument.presentation-template";
    if (!strcasecmp(suffix, ".ods"))
        return "application/vnd.oasis.opendocument.spreadsheet";
    if (!strcasecmp(suffix, ".ots"))
        return "application/vnd.oasis.opendocument.spreadsheet-template";
    if (!strcasecmp(suffix, ".odt"))
        return "application/vnd.oasis.opendocument.text";
    if (!strcasecmp(suffix, ".odm"))
        return "application/vnd.oasis.opendocument.text-master";
    if (!strcasecmp(suffix, ".ott"))
        return "application/vnd.oasis.opendocument.text-template";
    if (!strcasecmp(suffix, ".oth"))
        return "application/vnd.oasis.opendocument.text-web";
    if (!strcasecmp(suffix, ".pptx"))
        return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    if (!strcasecmp(suffix, ".sldx"))
        return "application/vnd.openxmlformats-officedocument.presentationml.slide";
    if (!strcasecmp(suffix, ".ppsx"))
        return "application/vnd.openxmlformats-officedocument.presentationml.slideshow";
    if (!strcasecmp(suffix, ".potx"))
        return "application/vnd.openxmlformats-officedocument.presentationml.template";
    if (!strcasecmp(suffix, ".xlsx"))
        return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    if (!strcasecmp(suffix, ".xltx"))
        return "application/vnd.openxmlformats-officedocument.spreadsheetml.template";
    if (!strcasecmp(suffix, ".docx"))
        return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    if (!strcasecmp(suffix, ".dotx"))
        return "application/vnd.openxmlformats-officedocument.wordprocessingml.template";
    if (!strcasecmp(suffix, ".cod"))
        return "application/vnd.rim.cod";
    if (!strcasecmp(suffix, ".mmf"))
        return "application/vnd.smaf";
    if (!strcasecmp(suffix, ".sdc"))
        return "application/vnd.stardivision.calc";
    if (!strcasecmp(suffix, ".sds"))
        return "application/vnd.stardivision.chart";
    if (!strcasecmp(suffix, ".sda"))
        return "application/vnd.stardivision.draw";
    if (!strcasecmp(suffix, ".sdd"))
        return "application/vnd.stardivision.impress";
    if (!strcasecmp(suffix, ".sdf"))
        return "application/vnd.stardivision.math";
    if (!strcasecmp(suffix, ".sdw"))
        return "application/vnd.stardivision.writer";
    if (!strcasecmp(suffix, ".sgl"))
        return "application/vnd.stardivision.writer-global";
    if (!strcasecmp(suffix, ".sxc"))
        return "application/vnd.sun.xml.calc";
    if (!strcasecmp(suffix, ".stc"))
        return "application/vnd.sun.xml.calc.template";
    if (!strcasecmp(suffix, ".sxd"))
        return "application/vnd.sun.xml.draw";
    if (!strcasecmp(suffix, ".std"))
        return "application/vnd.sun.xml.draw.template";
    if (!strcasecmp(suffix, ".sxi"))
        return "application/vnd.sun.xml.impress";
    if (!strcasecmp(suffix, ".sti"))
        return "application/vnd.sun.xml.impress.template";
    if (!strcasecmp(suffix, ".sxm"))
        return "application/vnd.sun.xml.math";
    if (!strcasecmp(suffix, ".sxw"))
        return "application/vnd.sun.xml.writer";
    if (!strcasecmp(suffix, ".sxg"))
        return "application/vnd.sun.xml.writer.global";
    if (!strcasecmp(suffix, ".stw"))
        return "application/vnd.sun.xml.writer.template";
    if (!strcasecmp(suffix, ".sis"))
        return "application/vnd.symbian.install";
    if (!strcasecmp(suffix, ".cap"))
        return "application/vnd.tcpdump.pcap";
    if (!strcasecmp(suffix, ".pcap"))
        return "application/vnd.tcpdump.pcap";
    if (!strcasecmp(suffix, ".vsd"))
        return "application/vnd.visio";
    if (!strcasecmp(suffix, ".vst"))
        return "application/vnd.visio";
    if (!strcasecmp(suffix, ".vsw"))
        return "application/vnd.visio";
    if (!strcasecmp(suffix, ".vss"))
        return "application/vnd.visio";
    if (!strcasecmp(suffix, ".wbxml"))
        return "application/vnd.wap.wbxml";
    if (!strcasecmp(suffix, ".wmlc"))
        return "application/vnd.wap.wmlc";
    if (!strcasecmp(suffix, ".wmlsc"))
        return "application/vnd.wap.wmlscriptc";
    if (!strcasecmp(suffix, ".wpd"))
        return "application/vnd.wordperfect";
    if (!strcasecmp(suffix, ".wp5"))
        return "application/vnd.wordperfect5.1";
    if (!strcasecmp(suffix, ".wk"))
        return "application/x-123";
    if (!strcasecmp(suffix, ".7z"))
        return "application/x-7z-compressed";
    if (!strcasecmp(suffix, ".abw"))
        return "application/x-abiword";
    if (!strcasecmp(suffix, ".dmg"))
        return "application/x-apple-diskimage";
    if (!strcasecmp(suffix, ".bcpio"))
        return "application/x-bcpio";
    if (!strcasecmp(suffix, ".torrent"))
        return "application/x-bittorrent";
    if (!strcasecmp(suffix, ".cab"))
        return "application/x-cab";
    if (!strcasecmp(suffix, ".cbr"))
        return "application/x-cbr";
    if (!strcasecmp(suffix, ".cbz"))
        return "application/x-cbz";
    if (!strcasecmp(suffix, ".cdf"))
        return "application/x-cdf";
    if (!strcasecmp(suffix, ".cda"))
        return "application/x-cdf";
    if (!strcasecmp(suffix, ".vcd"))
        return "application/x-cdlink";
    if (!strcasecmp(suffix, ".pgn"))
        return "application/x-chess-pgn";
    if (!strcasecmp(suffix, ".mph"))
        return "application/x-comsol";
    if (!strcasecmp(suffix, ".cpio"))
        return "application/x-cpio";
    if (!strcasecmp(suffix, ".csh"))
        return "application/x-csh";
    if (!strcasecmp(suffix, ".deb"))
        return "application/x-debian-package";
    if (!strcasecmp(suffix, ".udeb"))
        return "application/x-debian-package";
    if (!strcasecmp(suffix, ".dcr"))
        return "application/x-director";
    if (!strcasecmp(suffix, ".dir"))
        return "application/x-director";
    if (!strcasecmp(suffix, ".dxr"))
        return "application/x-director";
    if (!strcasecmp(suffix, ".dms"))
        return "application/x-dms";
    if (!strcasecmp(suffix, ".wad"))
        return "application/x-doom";
    if (!strcasecmp(suffix, ".dvi"))
        return "application/x-dvi";
    if (!strcasecmp(suffix, ".pfa"))
        return "application/x-font";
    if (!strcasecmp(suffix, ".pfb"))
        return "application/x-font";
    if (!strcasecmp(suffix, ".gsf"))
        return "application/x-font";
    if (!strcasecmp(suffix, ".pcf"))
        return "application/x-font-pcf";
    if (!strcasecmp(suffix, ".pcf.Z"))
        return "application/x-font-pcf";
    if (!strcasecmp(suffix, ".mm"))
        return "application/x-freemind";
    if (!strcasecmp(suffix, ".spl"))
        return "application/x-futuresplash";
    if (!strcasecmp(suffix, ".gan"))
        return "application/x-ganttproject";
    if (!strcasecmp(suffix, ".gnumeric"))
        return "application/x-gnumeric";
    if (!strcasecmp(suffix, ".sgf"))
        return "application/x-go-sgf";
    if (!strcasecmp(suffix, ".gcf"))
        return "application/x-graphing-calculator";
    if (!strcasecmp(suffix, ".gtar"))
        return "application/x-gtar";
    if (!strcasecmp(suffix, ".tgz"))
        return "application/x-gtar-compressed";
    if (!strcasecmp(suffix, ".taz"))
        return "application/x-gtar-compressed";
    if (!strcasecmp(suffix, ".hdf"))
        return "application/x-hdf";
    if (!strcasecmp(suffix, ".hwp"))
        return "application/x-hwp";
    if (!strcasecmp(suffix, ".ica"))
        return "application/x-ica";
    if (!strcasecmp(suffix, ".info"))
        return "application/x-info";
    if (!strcasecmp(suffix, ".ins"))
        return "application/x-internet-signup";
    if (!strcasecmp(suffix, ".isp"))
        return "application/x-internet-signup";
    if (!strcasecmp(suffix, ".iii"))
        return "application/x-iphone";
    if (!strcasecmp(suffix, ".iso"))
        return "application/x-iso9660-image";
    if (!strcasecmp(suffix, ".jam"))
        return "application/x-jam";
    if (!strcasecmp(suffix, ".jnlp"))
        return "application/x-java-jnlp-file";
    if (!strcasecmp(suffix, ".jmz"))
        return "application/x-jmol";
    if (!strcasecmp(suffix, ".chrt"))
        return "application/x-kchart";
    if (!strcasecmp(suffix, ".kil"))
        return "application/x-killustrator";
    if (!strcasecmp(suffix, ".skp"))
        return "application/x-koan";
    if (!strcasecmp(suffix, ".skd"))
        return "application/x-koan";
    if (!strcasecmp(suffix, ".skt"))
        return "application/x-koan";
    if (!strcasecmp(suffix, ".skm"))
        return "application/x-koan";
    if (!strcasecmp(suffix, ".kpr"))
        return "application/x-kpresenter";
    if (!strcasecmp(suffix, ".kpt"))
        return "application/x-kpresenter";
    if (!strcasecmp(suffix, ".ksp"))
        return "application/x-kspread";
    if (!strcasecmp(suffix, ".kwd"))
        return "application/x-kword";
    if (!strcasecmp(suffix, ".kwt"))
        return "application/x-kword";
    if (!strcasecmp(suffix, ".latex"))
        return "application/x-latex";
    if (!strcasecmp(suffix, ".lha"))
        return "application/x-lha";
    if (!strcasecmp(suffix, ".lyx"))
        return "application/x-lyx";
    if (!strcasecmp(suffix, ".lzh"))
        return "application/x-lzh";
    if (!strcasecmp(suffix, ".lzx"))
        return "application/x-lzx";
    if (!strcasecmp(suffix, ".frm"))
        return "application/x-maker";
    if (!strcasecmp(suffix, ".maker"))
        return "application/x-maker";
    if (!strcasecmp(suffix, ".frame"))
        return "application/x-maker";
    if (!strcasecmp(suffix, ".fm"))
        return "application/x-maker";
    if (!strcasecmp(suffix, ".fb"))
        return "application/x-maker";
    if (!strcasecmp(suffix, ".book"))
        return "application/x-maker";
    if (!strcasecmp(suffix, ".fbdoc"))
        return "application/x-maker";
    if (!strcasecmp(suffix, ".mif"))
        return "application/x-mif";
    if (!strcasecmp(suffix, ".m3u8"))
        return "application/x-mpegURL";
    if (!strcasecmp(suffix, ".application"))
        return "application/x-ms-application";
    if (!strcasecmp(suffix, ".manifest"))
        return "application/x-ms-manifest";
    if (!strcasecmp(suffix, ".wmd"))
        return "application/x-ms-wmd";
    if (!strcasecmp(suffix, ".wmz"))
        return "application/x-ms-wmz";
    if (!strcasecmp(suffix, ".com"))
        return "application/x-msdos-program";
    if (!strcasecmp(suffix, ".exe"))
        return "application/x-msdos-program";
    if (!strcasecmp(suffix, ".bat"))
        return "application/x-msdos-program";
    if (!strcasecmp(suffix, ".dll"))
        return "application/x-msdos-program";
    if (!strcasecmp(suffix, ".msi"))
        return "application/x-msi";
    if (!strcasecmp(suffix, ".nc"))
        return "application/x-netcdf";
    if (!strcasecmp(suffix, ".pac"))
        return "application/x-ns-proxy-autoconfig";
    if (!strcasecmp(suffix, ".nwc"))
        return "application/x-nwc";
    if (!strcasecmp(suffix, ".o"))
        return "application/x-object";
    if (!strcasecmp(suffix, ".oza"))
        return "application/x-oz-application";
    if (!strcasecmp(suffix, ".p7r"))
        return "application/x-pkcs7-certreqresp";
    if (!strcasecmp(suffix, ".crl"))
        return "application/x-pkcs7-crl";
    if (!strcasecmp(suffix, ".pyc"))
        return "application/x-python-code";
    if (!strcasecmp(suffix, ".pyo"))
        return "application/x-python-code";
    if (!strcasecmp(suffix, ".qgs"))
        return "application/x-qgis";
    if (!strcasecmp(suffix, ".shp"))
        return "application/x-qgis";
    if (!strcasecmp(suffix, ".shx"))
        return "application/x-qgis";
    if (!strcasecmp(suffix, ".qtl"))
        return "application/x-quicktimeplayer";
    if (!strcasecmp(suffix, ".rdp"))
        return "application/x-rdp";
    if (!strcasecmp(suffix, ".rpm"))
        return "application/x-redhat-package-manager";
    if (!strcasecmp(suffix, ".rss"))
        return "application/x-rss+xml";
    if (!strcasecmp(suffix, ".rb"))
        return "application/x-ruby";
    if (!strcasecmp(suffix, ".sci"))
        return "application/x-scilab";
    if (!strcasecmp(suffix, ".sce"))
        return "application/x-scilab";
    if (!strcasecmp(suffix, ".xcos"))
        return "application/x-scilab-xcos";
    if (!strcasecmp(suffix, ".sh"))
        return "application/x-sh";
    if (!strcasecmp(suffix, ".shar"))
        return "application/x-shar";
    if (!strcasecmp(suffix, ".swf"))
        return "application/x-shockwave-flash";
    if (!strcasecmp(suffix, ".swfl"))
        return "application/x-shockwave-flash";
    if (!strcasecmp(suffix, ".scr"))
        return "application/x-silverlight";
    if (!strcasecmp(suffix, ".sql"))
        return "application/x-sql";
    if (!strcasecmp(suffix, ".sit"))
        return "application/x-stuffit";
    if (!strcasecmp(suffix, ".sitx"))
        return "application/x-stuffit";
    if (!strcasecmp(suffix, ".sv4cpio"))
        return "application/x-sv4cpio";
    if (!strcasecmp(suffix, ".sv4crc"))
        return "application/x-sv4crc";
    if (!strcasecmp(suffix, ".tar"))
        return "application/x-tar";
    if (!strcasecmp(suffix, ".tcl"))
        return "application/x-tcl";
    if (!strcasecmp(suffix, ".gf"))
        return "application/x-tex-gf";
    if (!strcasecmp(suffix, ".pk"))
        return "application/x-tex-pk";
    if (!strcasecmp(suffix, ".texinfo"))
        return "application/x-texinfo";
    if (!strcasecmp(suffix, ".texi"))
        return "application/x-texinfo";
    if (!strcasecmp(suffix, ".~"))
        return "application/x-trash";
    if (!strcasecmp(suffix, ".%"))
        return "application/x-trash";
    if (!strcasecmp(suffix, ".bak"))
        return "application/x-trash";
    if (!strcasecmp(suffix, ".old"))
        return "application/x-trash";
    if (!strcasecmp(suffix, ".sik"))
        return "application/x-trash";
    if (!strcasecmp(suffix, ".t"))
        return "application/x-troff";
    if (!strcasecmp(suffix, ".tr"))
        return "application/x-troff";
    if (!strcasecmp(suffix, ".roff"))
        return "application/x-troff";
    if (!strcasecmp(suffix, ".man"))
        return "application/x-troff-man";
    if (!strcasecmp(suffix, ".me"))
        return "application/x-troff-me";
    if (!strcasecmp(suffix, ".ms"))
        return "application/x-troff-ms";
    if (!strcasecmp(suffix, ".ustar"))
        return "application/x-ustar";
    if (!strcasecmp(suffix, ".src"))
        return "application/x-wais-source";
    if (!strcasecmp(suffix, ".wz"))
        return "application/x-wingz";
    if (!strcasecmp(suffix, ".crt"))
        return "application/x-x509-ca-cert";
    if (!strcasecmp(suffix, ".xcf"))
        return "application/x-xcf";
    if (!strcasecmp(suffix, ".fig"))
        return "application/x-xfig";
    if (!strcasecmp(suffix, ".xpi"))
        return "application/x-xpinstall";
    if (!strcasecmp(suffix, ".xz"))
        return "application/x-xz";
    if (!strcasecmp(suffix, ".amr"))
        return "audio/amr";
    if (!strcasecmp(suffix, ".awb"))
        return "audio/amr-wb";
    if (!strcasecmp(suffix, ".axa"))
        return "audio/annodex";
    if (!strcasecmp(suffix, ".au"))
        return "audio/basic";
    if (!strcasecmp(suffix, ".snd"))
        return "audio/basic";
    if (!strcasecmp(suffix, ".csd"))
        return "audio/csound";
    if (!strcasecmp(suffix, ".orc"))
        return "audio/csound";
    if (!strcasecmp(suffix, ".sco"))
        return "audio/csound";
    if (!strcasecmp(suffix, ".flac"))
        return "audio/flac";
    if (!strcasecmp(suffix, ".mid"))
        return "audio/midi";
    if (!strcasecmp(suffix, ".midi"))
        return "audio/midi";
    if (!strcasecmp(suffix, ".kar"))
        return "audio/midi";
    if (!strcasecmp(suffix, ".mpga"))
        return "audio/mpeg";
    if (!strcasecmp(suffix, ".mpega"))
        return "audio/mpeg";
    if (!strcasecmp(suffix, ".mp2"))
        return "audio/mpeg";
    if (!strcasecmp(suffix, ".mp3"))
        return "audio/mpeg";
    if (!strcasecmp(suffix, ".m4a"))
        return "audio/mpeg";
    if (!strcasecmp(suffix, ".m3u"))
        return "audio/mpegurl";
    if (!strcasecmp(suffix, ".oga"))
        return "audio/ogg";
    if (!strcasecmp(suffix, ".ogg"))
        return "audio/ogg";
    if (!strcasecmp(suffix, ".opus"))
        return "audio/ogg";
    if (!strcasecmp(suffix, ".spx"))
        return "audio/ogg";
    if (!strcasecmp(suffix, ".sid"))
        return "audio/prs.sid";
    if (!strcasecmp(suffix, ".aif"))
        return "audio/x-aiff";
    if (!strcasecmp(suffix, ".aiff"))
        return "audio/x-aiff";
    if (!strcasecmp(suffix, ".aifc"))
        return "audio/x-aiff";
    if (!strcasecmp(suffix, ".gsm"))
        return "audio/x-gsm";
    if (!strcasecmp(suffix, ".m3u"))
        return "audio/x-mpegurl";
    if (!strcasecmp(suffix, ".wma"))
        return "audio/x-ms-wma";
    if (!strcasecmp(suffix, ".wax"))
        return "audio/x-ms-wax";
    if (!strcasecmp(suffix, ".ra"))
        return "audio/x-pn-realaudio";
    if (!strcasecmp(suffix, ".rm"))
        return "audio/x-pn-realaudio";
    if (!strcasecmp(suffix, ".ram"))
        return "audio/x-pn-realaudio";
    if (!strcasecmp(suffix, ".ra"))
        return "audio/x-realaudio";
    if (!strcasecmp(suffix, ".pls"))
        return "audio/x-scpls";
    if (!strcasecmp(suffix, ".sd2"))
        return "audio/x-sd2";
    if (!strcasecmp(suffix, ".wav"))
        return "audio/x-wav";
    if (!strcasecmp(suffix, ".alc"))
        return "chemical/x-alchemy";
    if (!strcasecmp(suffix, ".cac"))
        return "chemical/x-cache";
    if (!strcasecmp(suffix, ".cache"))
        return "chemical/x-cache";
    if (!strcasecmp(suffix, ".csf"))
        return "chemical/x-cache-csf";
    if (!strcasecmp(suffix, ".cbin"))
        return "chemical/x-cactvs-binary";
    if (!strcasecmp(suffix, ".cascii"))
        return "chemical/x-cactvs-binary";
    if (!strcasecmp(suffix, ".ctab"))
        return "chemical/x-cactvs-binary";
    if (!strcasecmp(suffix, ".cdx"))
        return "chemical/x-cdx";
    if (!strcasecmp(suffix, ".cer"))
        return "chemical/x-cerius";
    if (!strcasecmp(suffix, ".c3d"))
        return "chemical/x-chem3d";
    if (!strcasecmp(suffix, ".chm"))
        return "chemical/x-chemdraw";
    if (!strcasecmp(suffix, ".cif"))
        return "chemical/x-cif";
    if (!strcasecmp(suffix, ".cmdf"))
        return "chemical/x-cmdf";
    if (!strcasecmp(suffix, ".cml"))
        return "chemical/x-cml";
    if (!strcasecmp(suffix, ".cpa"))
        return "chemical/x-compass";
    if (!strcasecmp(suffix, ".bsd"))
        return "chemical/x-crossfire";
    if (!strcasecmp(suffix, ".csml"))
        return "chemical/x-csml";
    if (!strcasecmp(suffix, ".csm"))
        return "chemical/x-csml";
    if (!strcasecmp(suffix, ".ctx"))
        return "chemical/x-ctx";
    if (!strcasecmp(suffix, ".cxf"))
        return "chemical/x-cxf";
    if (!strcasecmp(suffix, ".cef"))
        return "chemical/x-cxf";
    if (!strcasecmp(suffix, ".emb"))
        return "chemical/x-embl-dl-nucleotide";
    if (!strcasecmp(suffix, ".embl"))
        return "chemical/x-embl-dl-nucleotide";
    if (!strcasecmp(suffix, ".spc"))
        return "chemical/x-galactic-spc";
    if (!strcasecmp(suffix, ".inp"))
        return "chemical/x-gamess-input";
    if (!strcasecmp(suffix, ".gam"))
        return "chemical/x-gamess-input";
    if (!strcasecmp(suffix, ".gamin"))
        return "chemical/x-gamess-input";
    if (!strcasecmp(suffix, ".fch"))
        return "chemical/x-gaussian-checkpoint";
    if (!strcasecmp(suffix, ".fchk"))
        return "chemical/x-gaussian-checkpoint";
    if (!strcasecmp(suffix, ".cub"))
        return "chemical/x-gaussian-cube";
    if (!strcasecmp(suffix, ".gau"))
        return "chemical/x-gaussian-input";
    if (!strcasecmp(suffix, ".gjc"))
        return "chemical/x-gaussian-input";
    if (!strcasecmp(suffix, ".gjf"))
        return "chemical/x-gaussian-input";
    if (!strcasecmp(suffix, ".gal"))
        return "chemical/x-gaussian-log";
    if (!strcasecmp(suffix, ".gcg"))
        return "chemical/x-gcg8-sequence";
    if (!strcasecmp(suffix, ".gen"))
        return "chemical/x-genbank";
    if (!strcasecmp(suffix, ".hin"))
        return "chemical/x-hin";
    if (!strcasecmp(suffix, ".istr"))
        return "chemical/x-isostar";
    if (!strcasecmp(suffix, ".ist"))
        return "chemical/x-isostar";
    if (!strcasecmp(suffix, ".jdx"))
        return "chemical/x-jcamp-dx";
    if (!strcasecmp(suffix, ".dx"))
        return "chemical/x-jcamp-dx";
    if (!strcasecmp(suffix, ".kin"))
        return "chemical/x-kinemage";
    if (!strcasecmp(suffix, ".mcm"))
        return "chemical/x-macmolecule";
    if (!strcasecmp(suffix, ".mmd"))
        return "chemical/x-macromodel-input";
    if (!strcasecmp(suffix, ".mmod"))
        return "chemical/x-macromodel-input";
    if (!strcasecmp(suffix, ".mol"))
        return "chemical/x-mdl-molfile";
    if (!strcasecmp(suffix, ".rd"))
        return "chemical/x-mdl-rdfile";
    if (!strcasecmp(suffix, ".rxn"))
        return "chemical/x-mdl-rxnfile";
    if (!strcasecmp(suffix, ".sd"))
        return "chemical/x-mdl-sdfile";
    if (!strcasecmp(suffix, ".sdf"))
        return "chemical/x-mdl-sdfile";
    if (!strcasecmp(suffix, ".tgf"))
        return "chemical/x-mdl-tgf";
    if (!strcasecmp(suffix, ".mcif"))
        return "chemical/x-mmcif";
    if (!strcasecmp(suffix, ".mol2"))
        return "chemical/x-mol2";
    if (!strcasecmp(suffix, ".b"))
        return "chemical/x-molconn-Z";
    if (!strcasecmp(suffix, ".gpt"))
        return "chemical/x-mopac-graph";
    if (!strcasecmp(suffix, ".mop"))
        return "chemical/x-mopac-input";
    if (!strcasecmp(suffix, ".mopcrt"))
        return "chemical/x-mopac-input";
    if (!strcasecmp(suffix, ".mpc"))
        return "chemical/x-mopac-input";
    if (!strcasecmp(suffix, ".zmt"))
        return "chemical/x-mopac-input";
    if (!strcasecmp(suffix, ".moo"))
        return "chemical/x-mopac-out";
    if (!strcasecmp(suffix, ".mvb"))
        return "chemical/x-mopac-vib";
    if (!strcasecmp(suffix, ".asn"))
        return "chemical/x-ncbi-asn1";
    if (!strcasecmp(suffix, ".prt"))
        return "chemical/x-ncbi-asn1-ascii";
    if (!strcasecmp(suffix, ".ent"))
        return "chemical/x-ncbi-asn1-ascii";
    if (!strcasecmp(suffix, ".val"))
        return "chemical/x-ncbi-asn1-binary";
    if (!strcasecmp(suffix, ".aso"))
        return "chemical/x-ncbi-asn1-binary";
    if (!strcasecmp(suffix, ".asn"))
        return "chemical/x-ncbi-asn1-spec";
    if (!strcasecmp(suffix, ".pdb"))
        return "chemical/x-pdb";
    if (!strcasecmp(suffix, ".ent"))
        return "chemical/x-pdb";
    if (!strcasecmp(suffix, ".ros"))
        return "chemical/x-rosdal";
    if (!strcasecmp(suffix, ".sw"))
        return "chemical/x-swissprot";
    if (!strcasecmp(suffix, ".vms"))
        return "chemical/x-vamas-iso14976";
    if (!strcasecmp(suffix, ".vmd"))
        return "chemical/x-vmd";
    if (!strcasecmp(suffix, ".xtel"))
        return "chemical/x-xtel";
    if (!strcasecmp(suffix, ".xyz"))
        return "chemical/x-xyz";
    if (!strcasecmp(suffix, ".ttc"))
        return "font/collection";
    if (!strcasecmp(suffix, ".ttf"))
        return "font/otf";
    if (!strcasecmp(suffix, ".otf"))
        return "font/otf";
    if (!strcasecmp(suffix, ".ttf"))
        return "font/sfnt";
    if (!strcasecmp(suffix, ".otf"))
        return "font/sfnt";
    if (!strcasecmp(suffix, ".ttf"))
        return "font/ttf";
    if (!strcasecmp(suffix, ".otf"))
        return "font/ttf";
    if (!strcasecmp(suffix, ".woff"))
        return "font/woff";
    if (!strcasecmp(suffix, ".woff2"))
        return "font/woff2";
    if (!strcasecmp(suffix, ".gif"))
        return "image/gif";
    if (!strcasecmp(suffix, ".ief"))
        return "image/ief";
    if (!strcasecmp(suffix, ".jp2"))
        return "image/jp2";
    if (!strcasecmp(suffix, ".jpg2"))
        return "image/jp2";
    if (!strcasecmp(suffix, ".jpeg"))
        return "image/jpeg";
    if (!strcasecmp(suffix, ".jpg"))
        return "image/jpeg";
    if (!strcasecmp(suffix, ".jpe"))
        return "image/jpeg";
    if (!strcasecmp(suffix, ".jpm"))
        return "image/jpm";
    if (!strcasecmp(suffix, ".jpx"))
        return "image/jpx";
    if (!strcasecmp(suffix, ".jpf"))
        return "image/jpx";
    if (!strcasecmp(suffix, ".pcx"))
        return "image/pcx";
    if (!strcasecmp(suffix, ".png"))
        return "image/png";
    if (!strcasecmp(suffix, ".svg"))
        return "image/svg+xml";
    if (!strcasecmp(suffix, ".svgz"))
        return "image/svg+xml";
    if (!strcasecmp(suffix, ".tiff"))
        return "image/tiff";
    if (!strcasecmp(suffix, ".tif"))
        return "image/tiff";
    if (!strcasecmp(suffix, ".djvu"))
        return "image/vnd.djvu";
    if (!strcasecmp(suffix, ".djv"))
        return "image/vnd.djvu";
    if (!strcasecmp(suffix, ".ico"))
        return "image/vnd.microsoft.icon";
    if (!strcasecmp(suffix, ".wbmp"))
        return "image/vnd.wap.wbmp";
    if (!strcasecmp(suffix, ".cr2"))
        return "image/x-canon-cr2";
    if (!strcasecmp(suffix, ".crw"))
        return "image/x-canon-crw";
    if (!strcasecmp(suffix, ".ras"))
        return "image/x-cmu-raster";
    if (!strcasecmp(suffix, ".cdr"))
        return "image/x-coreldraw";
    if (!strcasecmp(suffix, ".pat"))
        return "image/x-coreldrawpattern";
    if (!strcasecmp(suffix, ".cdt"))
        return "image/x-coreldrawtemplate";
    if (!strcasecmp(suffix, ".cpt"))
        return "image/x-corelphotopaint";
    if (!strcasecmp(suffix, ".erf"))
        return "image/x-epson-erf";
    if (!strcasecmp(suffix, ".art"))
        return "image/x-jg";
    if (!strcasecmp(suffix, ".jng"))
        return "image/x-jng";
    if (!strcasecmp(suffix, ".bmp"))
        return "image/x-ms-bmp";
    if (!strcasecmp(suffix, ".nef"))
        return "image/x-nikon-nef";
    if (!strcasecmp(suffix, ".orf"))
        return "image/x-olympus-orf";
    if (!strcasecmp(suffix, ".psd"))
        return "image/x-photoshop";
    if (!strcasecmp(suffix, ".pnm"))
        return "image/x-portable-anymap";
    if (!strcasecmp(suffix, ".pbm"))
        return "image/x-portable-bitmap";
    if (!strcasecmp(suffix, ".pgm"))
        return "image/x-portable-graymap";
    if (!strcasecmp(suffix, ".ppm"))
        return "image/x-portable-pixmap";
    if (!strcasecmp(suffix, ".rgb"))
        return "image/x-rgb";
    if (!strcasecmp(suffix, ".xbm"))
        return "image/x-xbitmap";
    if (!strcasecmp(suffix, ".xpm"))
        return "image/x-xpixmap";
    if (!strcasecmp(suffix, ".xwd"))
        return "image/x-xwindowdump";
    if (!strcasecmp(suffix, ".eml"))
        return "message/rfc822";
    if (!strcasecmp(suffix, ".igs"))
        return "model/iges";
    if (!strcasecmp(suffix, ".iges"))
        return "model/iges";
    if (!strcasecmp(suffix, ".msh"))
        return "model/mesh";
    if (!strcasecmp(suffix, ".mesh"))
        return "model/mesh";
    if (!strcasecmp(suffix, ".silo"))
        return "model/mesh";
    if (!strcasecmp(suffix, ".wrl"))
        return "model/vrml";
    if (!strcasecmp(suffix, ".vrml"))
        return "model/vrml";
    if (!strcasecmp(suffix, ".x3dv"))
        return "model/x3d+vrml";
    if (!strcasecmp(suffix, ".x3d"))
        return "model/x3d+xml";
    if (!strcasecmp(suffix, ".x3db"))
        return "model/x3d+binary";
    if (!strcasecmp(suffix, ".appcache"))
        return "text/cache-manifest";
    if (!strcasecmp(suffix, ".ics"))
        return "text/calendar";
    if (!strcasecmp(suffix, ".icz"))
        return "text/calendar";
    if (!strcasecmp(suffix, ".css"))
        return "text/css";
    if (!strcasecmp(suffix, ".csv"))
        return "text/csv";
    if (!strcasecmp(suffix, ".323"))
        return "text/h323";
    if (!strcasecmp(suffix, ".html"))
        return "text/html";
    if (!strcasecmp(suffix, ".htm"))
        return "text/html";
    if (!strcasecmp(suffix, ".shtml"))
        return "text/html";
    if (!strcasecmp(suffix, ".uls"))
        return "text/iuls";
    if (!strcasecmp(suffix, ".mml"))
        return "text/mathml";
    if (!strcasecmp(suffix, ".asc"))
        return "text/plain";
    if (!strcasecmp(suffix, ".txt"))
        return "text/plain";
    if (!strcasecmp(suffix, ".text"))
        return "text/plain";
    if (!strcasecmp(suffix, ".pot"))
        return "text/plain";
    if (!strcasecmp(suffix, ".brf"))
        return "text/plain";
    if (!strcasecmp(suffix, ".srt"))
        return "text/plain";
    if (!strcasecmp(suffix, ".rtx"))
        return "text/richtext";
    if (!strcasecmp(suffix, ".sct"))
        return "text/scriptlet";
    if (!strcasecmp(suffix, ".wsc"))
        return "text/scriptlet";
    if (!strcasecmp(suffix, ".tm"))
        return "text/texmacs";
    if (!strcasecmp(suffix, ".tsv"))
        return "text/tab-separated-values";
    if (!strcasecmp(suffix, ".ttl"))
        return "text/turtle";
    if (!strcasecmp(suffix, ".vcf"))
        return "text/vcard";
    if (!strcasecmp(suffix, ".vcard"))
        return "text/vcard";
    if (!strcasecmp(suffix, ".jad"))
        return "text/vnd.sun.j2me.app-descriptor";
    if (!strcasecmp(suffix, ".wml"))
        return "text/vnd.wap.wml";
    if (!strcasecmp(suffix, ".wmls"))
        return "text/vnd.wap.wmlscript";
    if (!strcasecmp(suffix, ".bib"))
        return "text/x-bibtex";
    if (!strcasecmp(suffix, ".boo"))
        return "text/x-boo";
    if (!strcasecmp(suffix, ".h++"))
        return "text/x-c++hdr";
    if (!strcasecmp(suffix, ".hpp"))
        return "text/x-c++hdr";
    if (!strcasecmp(suffix, ".hxx"))
        return "text/x-c++hdr";
    if (!strcasecmp(suffix, ".hh"))
        return "text/x-c++hdr";
    if (!strcasecmp(suffix, ".c++"))
        return "text/x-c++src";
    if (!strcasecmp(suffix, ".cpp"))
        return "text/x-c++src";
    if (!strcasecmp(suffix, ".cxx"))
        return "text/x-c++src";
    if (!strcasecmp(suffix, ".cc"))
        return "text/x-c++src";
    if (!strcasecmp(suffix, ".h"))
        return "text/x-chdr";
    if (!strcasecmp(suffix, ".htc"))
        return "text/x-component";
    if (!strcasecmp(suffix, ".csh"))
        return "text/x-csh";
    if (!strcasecmp(suffix, ".c"))
        return "text/x-csrc";
    if (!strcasecmp(suffix, ".d"))
        return "text/x-dsrc";
    if (!strcasecmp(suffix, ".diff"))
        return "text/x-diff";
    if (!strcasecmp(suffix, ".patch"))
        return "text/x-diff";
    if (!strcasecmp(suffix, ".hs"))
        return "text/x-haskell";
    if (!strcasecmp(suffix, ".java"))
        return "text/x-java";
    if (!strcasecmp(suffix, ".ly"))
        return "text/x-lilypond";
    if (!strcasecmp(suffix, ".lhs"))
        return "text/x-literate-haskell";
    if (!strcasecmp(suffix, ".moc"))
        return "text/x-moc";
    if (!strcasecmp(suffix, ".p"))
        return "text/x-pascal";
    if (!strcasecmp(suffix, ".pas"))
        return "text/x-pascal";
    if (!strcasecmp(suffix, ".gcd"))
        return "text/x-pcs-gcd";
    if (!strcasecmp(suffix, ".pl"))
        return "text/x-perl";
    if (!strcasecmp(suffix, ".pm"))
        return "text/x-perl";
    if (!strcasecmp(suffix, ".py"))
        return "text/x-python";
    if (!strcasecmp(suffix, ".scala"))
        return "text/x-scala";
    if (!strcasecmp(suffix, ".etx"))
        return "text/x-setext";
    if (!strcasecmp(suffix, ".sfv"))
        return "text/x-sfv";
    if (!strcasecmp(suffix, ".sh"))
        return "text/x-sh";
    if (!strcasecmp(suffix, ".tcl"))
        return "text/x-tcl";
    if (!strcasecmp(suffix, ".tk"))
        return "text/x-tcl";
    if (!strcasecmp(suffix, ".tex"))
        return "text/x-tex";
    if (!strcasecmp(suffix, ".ltx"))
        return "text/x-tex";
    if (!strcasecmp(suffix, ".sty"))
        return "text/x-tex";
    if (!strcasecmp(suffix, ".cls"))
        return "text/x-tex";
    if (!strcasecmp(suffix, ".vcs"))
        return "text/x-vcalendar";
    if (!strcasecmp(suffix, ".3gp"))
        return "video/3gpp";
    if (!strcasecmp(suffix, ".axv"))
        return "video/annodex";
    if (!strcasecmp(suffix, ".dl"))
        return "video/dl";
    if (!strcasecmp(suffix, ".dif"))
        return "video/dv";
    if (!strcasecmp(suffix, ".dv"))
        return "video/dv";
    if (!strcasecmp(suffix, ".fli"))
        return "video/fli";
    if (!strcasecmp(suffix, ".gl"))
        return "video/gl";
    if (!strcasecmp(suffix, ".mpeg"))
        return "video/mpeg";
    if (!strcasecmp(suffix, ".mpg"))
        return "video/mpeg";
    if (!strcasecmp(suffix, ".mpe"))
        return "video/mpeg";
    if (!strcasecmp(suffix, ".ts"))
        return "video/MP2T";
    if (!strcasecmp(suffix, ".mp4"))
        return "video/mp4";
    if (!strcasecmp(suffix, ".qt"))
        return "video/quicktime";
    if (!strcasecmp(suffix, ".mov"))
        return "video/quicktime";
    if (!strcasecmp(suffix, ".ogv"))
        return "video/ogg";
    if (!strcasecmp(suffix, ".webm"))
        return "video/webm";
    if (!strcasecmp(suffix, ".mxu"))
        return "video/vnd.mpegurl";
    if (!strcasecmp(suffix, ".flv"))
        return "video/x-flv";
    if (!strcasecmp(suffix, ".lsf"))
        return "video/x-la-asf";
    if (!strcasecmp(suffix, ".lsx"))
        return "video/x-la-asf";
    if (!strcasecmp(suffix, ".mng"))
        return "video/x-mng";
    if (!strcasecmp(suffix, ".asf"))
        return "video/x-ms-asf";
    if (!strcasecmp(suffix, ".asx"))
        return "video/x-ms-asf";
    if (!strcasecmp(suffix, ".wm"))
        return "video/x-ms-wm";
    if (!strcasecmp(suffix, ".wmv"))
        return "video/x-ms-wmv";
    if (!strcasecmp(suffix, ".wmx"))
        return "video/x-ms-wmx";
    if (!strcasecmp(suffix, ".wvx"))
        return "video/x-ms-wvx";
    if (!strcasecmp(suffix, ".avi"))
        return "video/x-msvideo";
    if (!strcasecmp(suffix, ".movie"))
        return "video/x-sgi-movie";
    if (!strcasecmp(suffix, ".mpv"))
        return "video/x-matroska";
    if (!strcasecmp(suffix, ".mkv"))
        return "video/x-matroska";
    if (!strcasecmp(suffix, ".ice"))
        return "x-conference/x-cooltalk";
    if (!strcasecmp(suffix, ".sisx"))
        return "x-epoc/x-sisx-app";
    if (!strcasecmp(suffix, ".vrm"))
        return "x-world/x-vrml";
    if (!strcasecmp(suffix, ".vrml"))
        return "x-world/x-vrml";
    if (!strcasecmp(suffix, ".wrl"))
        return "x-world/x-vrml";
    return "application/binary";
}
