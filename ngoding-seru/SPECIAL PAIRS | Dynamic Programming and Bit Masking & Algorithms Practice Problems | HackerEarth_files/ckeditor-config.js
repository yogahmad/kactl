/*
 *   ckeditor-config.js
 *
 *   In addition to CKEditor configurations written in god/ckeditor_settings.py,
 *   this file takes care of all the CKEditor related stuff. To prevent the
 *   overhead of modifying the CKEditor scripts, we decided to customize the
 *   CKEditor fields using the script written in this file. If we plan to
 *   upgrade CKEditor in future, we need to make changes in this file only.
 *
 *   You will find some constants used in this file that are fetched from
 *   templates/constants/ckeditor/constants.html. This is done to take care of
 *   the translations of the strings defined in those constants.
 *
 */(function(){function a(a,b,c){return function(){var d=this.getValue(),e=!!(CKEDITOR.dialog.validate.integer()(d)&&d>=b&&d<=c);return e||(alert(a),this.select()),e}}function b(a){for(var b in CKEDITOR.instances){var c=CKEDITOR.instances[b];c.getCommand("maximize").state===1&&a&&a.keyCode===27&&c.execCommand("maximize")}}CKEDITOR.on("instanceReady",function(a){var c=a.editor;document.onkeydown=function(a){b(a||window.event)},c.on("key",function(a){b(a.data)}),c.removeMenuItem("paste"),c.removeMenuItem("tablecell");var d=c.dataProcessor.htmlFilter,e={priority:10,applyToAll:!0};d.addRules({comment:function(){return!1}},e),d.addRules({elements:{pre:function(a){a.children[0].name==="code"&&(a.attributes.class="prettyprint")}}},e)}),CKEDITOR.on("dialogDefinition",function(b){var c=b.data,d=c.name,e=c.definition,f=e.getContents("info");if(d==="link"){f.remove("browse");var g=f.get("linkType");g.items=[[URL_TEXT,"url"],[EMAIL_TEXT,"email"]];var h=f.get("protocol");h.items=[["http://","http://"],["https://","https://"]];var i=e.getContents("target"),j=i.get("linkTargetType");j["default"]="_blank"}else if(d==="image2"){f.remove("browse");var k=e.getContents("Upload");k.elements[0].label=UPLOAD_IMAGE,k.elements[1].label=UPLOAD_IMAGE}else if(d==="table"||d==="tableProperties"){var l=f.get("txtRows"),m=1,n=100;l.validate=a(VALIDATE_NUM_ROWS.format({minValue:m,maxValue:n}),m,n);var o=f.get("txtCols"),p=1,q=25;o.validate=a(VALIDATE_NUM_COLS.format({minValue:p,maxValue:q}),p,q),f.remove("selHeaders"),f.remove("txtCellSpace"),f.remove("txtCellPad"),f.remove("txtSummary")}else d==="codeSnippet"&&f.remove("lang")})})();