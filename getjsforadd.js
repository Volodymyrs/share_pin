(function(){
	var localhost = "star-auction.com";
	var localhost_url = "http://"+localhost;
	var module_path = localhost_url+"/sites/all/modules/custom/share_pin";
	var localhost_repl = localhost.replace(/\./g, "\\.");
	var reg = "/(?:https?:\/\/)?(?:www\.)?"+localhost_repl+"/";
	if(document.getElementById("starauction_img_container")) return false;
	//if(location.href.match(/(?:https?:\/\/)?(?:www\.)?katmary\.net/)) {
    //alert(reg);
	if(location.href.match(reg)) {
		//alert('кнопка Katmary Pin успешно установлена, теперь вы можете добавлять контент с других сайтов');
		alert('button Katmary pin was added');
		return false;
	}
	var origin_body_style = {
		"display": document.body.style.display,
		"width" : document.body.style.width,
		"overflow" : document.body.style.overflow
	};
	var params = {
		minHeight : 50,
		maxHeight : 1280,
		minWidth : 50,
		maxWidth : 1280,
		css_classes : {
			container_class : "position: absolute; left: 0px; top: 0px; z-index: 2147483647; width:100%;  border: 0",
			ifr_class: "position: absolute; left: 0px; top: 0px; background-color:#ccc; z-index: 2147483647; width:100%;  border: 0; opacity: 0.9",
			anchor_class : "",
			span_class : "width: 200px; height:200px; padding: 10px; float:left",
			close_div_class : "cursor: pointer; text-align: center; font-size: 20px; padding: 10px; margin-bottom:10px; background-color:#ececec; position:fixed; left:0px; top:0px; width:100%"
		},
		new_window_params : {
			options : "status=no,resizable=0,personalbar=no,directories=no,location=no,toolbar=no,menubar=no,width=543,height=650,left=0,top=0",
			//url : "http://katmary.net/user/favorite/add",
			url : localhost_url+"/user/new-favorite/add",
			winName : "star"
		},
		firstSpanHTML : '<a href="'+localhost_url+'/">'+localhost_url+'/</a>',
		template : function(page_title){return '<div style="width: 100%; height: 64px; background:url('+module_path+'/images/pinwin_bgr_blue.png); position: fixed; z-index:1;">'+
			'<a href="'+localhost_url+'/"><div style="width: 25%; text-align: center; float: left; cursor: pointer; border: none !important;" onmouseover="this.style.background = \'url('+module_path+'/images/pinwin_bgr_hover.png)\'" onmouseout="this.style.background = \'\'">'+
				'<img style="position:static; border: none !important;" src="'+module_path+'/images/pinwin_logo.png">'+
			'</div></a>'+
			'<div style="height: 57px; width:50%; float: left; text-align:left; background: url('+module_path+'/images/pinwin_separator_top.png) no-repeat 0 0 transparent;">'+
				'<div style="color: #fff; font-family: Tahoma,arial; font-size: 18px; text-shadow: 1px 1px 0px #446EAE; margin: 8px 0px 0px 16px !important; line-height: 15px;">'+
					'Публикация страницы'+
				'</div>'+'<div style="display: block; height: 30px; overflow: hidden; margin-top: 4px;">'+
				'<div style="color: #fff;margin: 0 10px; height: 30px; display: table-cell; vertical-align: middle; padding-left: 17px; padding-right: 17px;"><span style="display: table-cell; line-height: 14px; font-size: 11px; font-family: Tahoma;">"'+
					page_title+
				'"</span></div>'+'</div>'+
			'</div>'+
			'<div onClick="document.body.removeChild(document.getElementById(\'starauction_img_container\')); document.body.style.display = \''+origin_body_style.display+'\'; document.body.style.width = \''+origin_body_style.width+'\'; document.body.style.overflow = \''+origin_body_style.overflow+'\';document.body.removeChild(document.getElementById(\'starauction_img_ifr\'))" style="width: 25%; height:57px; float: left; cursor:pointer; " onmouseover="this.style.background = \'url('+module_path+'/images/pinwin_bgr_hover.png)\'" onmouseout="this.style.background = \'\'">'+
				'<div style="width: 100%; height:100%; background: url('+module_path+'/images/pinwin_separator_top.png) no-repeat 0 0 transparent;">'+
					'<div  style="background: url('+module_path+'/images/pinwin_btn_cancel_ru.png) no-repeat 50% 50% transparent; height: 57px;">'+
					'</div>'+
				'</div>'+
			'</div>'+
		'</div>'+
		'<div style="width:100%; height: 100%; display: inline-block; margin-top: 70px; text-align: center;position:absolute; z-index: 2147483647;" id="katmary_img_container">'+
			'<a style="display: inline-block; text-decoration: none;" href="javascript:void((function(){window.open(\''
								+params.new_window_params.url
								+"?img_src="
	+"&win_title="+encodeURIComponent(document.title.replace("'", '`'))
	+"&url="+encodeURIComponent(encodeURIComponent(location.href))
	+"&description="+encodeURIComponent(getDescription())
	+"&page_encoding="+encodeURIComponent(get_page_encodding())
	+"', '"+params.new_window_params.winName+"', '"
	+params.new_window_params.options
	+"');document.body.style.display = \'"+origin_body_style.display+"\'; document.body.style.width = \'"+origin_body_style.width+"\'; document.body.style.overflow = \''+origin_body_style.overflow+'\';document.body.removeChild(document.getElementById('starauction_img_container'));document.body.removeChild(document.getElementById('starauction_img_ifr'));})())\">"+
				'<div style="width: 258px; height: 258px; podition:relative; float:left; margin: 6px; display: inline-block;">'+
					'<div onmouseover="this.style.background = \'url('+module_path+'/images/pinwin_item_hover.png)\'" onmouseout="this.style.background = \'url('+module_path+'/images/pinwin_item.png)\'" style="width: 258px; height: 258px; float: left; position: absolute; display: block; background: url('+module_path+'/images/pinwin_item.png) repeat scroll 0px 0px transparent;">'+
						'<div style="position: relative; top: 235px; color: #fff; font-family: Tahoma; font-size: 10px; text-align: center; width:100%; text-decoration: none !important; line-height: 16px;">392 ? 392</div>'+
					'</div>'+
				'<div style="width: 250px; height:250px; overflow:hidden; margin: 4px">'+
						'<img width="250" style="border: none !important; position:static;margin:-0px 0" src="'+module_path+'/images/layout/pin-wout-picture.png">'+
				'</div>'+
			'</div>'+
		'</a>'+
		'</div>';},
		get_img_template: function(img, url) {
			var img_w = img.offsetWidth ? img.offsetWidth : img.getAttribute('width'), img_h = img.offsetHeight ? img.offsetHeight : img.getAttribute('height');
			if(img_h < img_w) {
				var WorH = "height",
				margin = "0 -"+Math.round((250 - (img_h/img_w)*250))+"px"
			}
			else {
				//console.log(img_w+" "+img_h);
				var WorH = "width",
				margin = "-"+Math.round((250 - ((img_w/img_h)*250))/2)+"px 0";
			}
			return '<a href="'+url+'" style="display: inline-block; text-decoration: none;"><div style="width: 258px; height: 258px; podition:relative; float:left; margin: 6px; display: inline-block;">'+
				'<div style="background: url('+module_path+'/images/pinwin_item.png); width:258px; height:258px; float:left; position:absolute; display: block;" onmouseover="this.style.background = \'url('+module_path+'/images/pinwin_item_hover.png)\'" onmouseout="this.style.background = \'url('+module_path+'/images/pinwin_item.png)\'">	'+
				'<div style="position: relative; top: 235px; color: #fff; font-family: Tahoma; font-size: 10px; text-align: center; width:100%; text-decoration: none !important; line-height: 16px;">'+
					img_w+' ? '+img_h+
				'</div>'+
				'</div>'+
				'<div style="width: 250px; height:250px; overflow:hidden; margin: 4px">'+
					'<img src="'+img.getAttribute("src")+'" style="border: none !important; position:static;margin:'+margin+'" '+WorH+'="250" >'+
					(img.getAttribute('name') == 'pin_youtube_photo' ? '<div style="background: url('+module_path+'/images/pinwin_btn_video.png); width: 78px; height: 78px; margin:-170px 0 0 80px; position:relative;"></div>' : '')+
				'</div>'+
			'</div></a>';
		}
	}

	var result = new Array(),
		img, anchor, span, div_cont, div_img_size,
		j = 0,
		container = document.createElement("div"),
		ifr = document.createElement("iframe"),
		close_div = document.createElement("div");
	if(location.href.match(/^https?:\/\/www.youtube.com/)) {
		var get_youtube_image = (function(){
			var metas = document.getElementsByTagName('meta'),
				img_info = {};
			for(var j = 0; j  < metas.length; j++) {
				if(metas[j].getAttribute('property') == 'og:image')
					img_info.src = metas[j].getAttribute('content');
				if(metas[j].getAttribute('property') == 'og:video:width')
					img_info.w = metas[j].getAttribute('content');
				if(metas[j].getAttribute('property') == 'og:video:height')
					img_info.h = metas[j].getAttribute('content');
			}
			return img_info
		})();
		//console.log(get_youtube_image);
		var image  = document.createElement('img');
		image.setAttribute('src', get_youtube_image.src);
		image.setAttribute('width', get_youtube_image.w);
		image.setAttribute('height', get_youtube_image.h);
		image.offsetWidth = get_youtube_image.w;
		image.offsetHeight = get_youtube_image.h;
		image.setAttribute('name', 'pin_youtube_photo');
		//console.log(image);
		images = new Array();
		images[0] = image;
	}
	else {
		var images = document.getElementsByTagName("img");
	}
	//console.log(images);
	//close_div.setAttribute("onClick", "document.body.removeChild(document.getElementById('starauction_img_container'));document.body.removeChild(document.getElementById('starauction_img_ifr'))");
	close_div.innerHTML = "Отмена";
	close_div.setAttribute("style", params.css_classes.close_div_class);
	container.appendChild(close_div);
	span = document.createElement("div");
	span.setAttribute("style", params.css_classes.span_class);
	span.innerHTML = params.firstSpanHTML;
	var check_img = function(img) {
		//if(img.src.match(/katmary\.net/)) return false;
		if(img.src.match("/"+localhost_repl+"/")) return false;
		if(img.offsetHeight < params.minHeight || img.offsetHeight > params.maxHeight || img.offsetWidth < params.minWidth || img.offsetWidth > params.maxWidth || !img.getAttribute("src")) return false;
		if(!img.src.match(/^https?/)) return false;
		return true;
	}
	var get_page_encodding = function() {
		var metas = document.getElementsByTagName('meta'),
			i = metas.length;
		for(var j = 0; j<i; j++) {
		if(metas[j].getAttribute('http-equiv'))
			if(metas[j].getAttribute('http-equiv').match(/content\-type/i))
				return metas[j].getAttribute('content').match(/charset=([\w\d\-]+)/i)[1];
			}
	}
	var getHeight = function() {
		var doc_html = document.getElementsByTagName("html")[0]
		return Math.max(Math.max(document.body.scrollHeight, doc_html.scrollHeight), Math.max(document.body.offsetHeight, doc_html.offsetHeight), Math.max(document.body.clientHeight, doc_html.clientHeight));
    }
	var getDescription = function() {
		var metas = document.getElementsByTagName("meta");
		for(var i = 0; i < metas.length; i++) {
			if(metas[i].getAttribute("name") == "description") {
				var desc = metas[i].getAttribute("content");
				break;
			}
		}
		if(desc) return desc.replace(/^\s+/, '').replace("'", '`').replace(/\s+/g, ' ');
		return "";
	}
	ifr.setAttribute("id", "starauction_img_ifr");
	ifr.setAttribute("style", params.css_classes.ifr_class);
	ifr.style.height = getHeight()+"px";
	document.body.style.display = "inline-block";
	document.body.style.width = "100%";
	document.body.style.overflow = "visible";
	document.body.appendChild(ifr);
	container.setAttribute("id", "starauction_img_container");
 	container.setAttribute("style", params.css_classes.container_class);
	container.innerHTML = params.template(document.title);
	document.body.appendChild(container);
	var img_count = images.length;
	for(var i = 0; i < img_count; i++) {
	if(!location.href.match(/^https?:\/\/www.youtube.com/))
		if(!check_img(images[i])) continue;
		//result[j] = document.createElement("img");
		//result[j].setAttribute("src", images[i].getAttribute("src"));
	//	div_img_size = document.createElement('div');
		//div_img_size.innerHTML = images[i].offsetWidth + "&nbsp X&nbsp" + images[i].offsetHeight;
		//div_img_size.setAttribute('style', 'margin-left:65px');
// 		if(images[i].offsetWidth > images[i].offsetHeight) {
// 			result[j].setAttribute("width", "200");
// 		}
// 		else result[j].setAttribute("height", "200");
// 		if(j == 0) {
// 			container.appendChild(span);
// 		}
	//	result[j].setAttribute("id", "star_auction_img"+j);
	//	span = document.createElement("div");
	//	console.log(document.getElementById("katmary_img_container"));
	//console.log(images[i]);
		document.getElementById("katmary_img_container").innerHTML += params.get_img_template(images[i], "javascript:void((function(){window.open('"
								+params.new_window_params.url
								+"?img_src="+encodeURIComponent(images[i].src)
								+"&win_title="+encodeURIComponent(document.title.replace("'", '`'))
								+"&url="+encodeURIComponent(encodeURIComponent(location.href))
								+"&description="+encodeURIComponent(getDescription(images[i]))
								+"&page_encoding="+encodeURIComponent(get_page_encodding())
								+"', '"+params.new_window_params.winName+"', '"
								+params.new_window_params.options
								+"');document.body.style.display = \'"+origin_body_style.display+"\'; document.body.style.width = \'"+origin_body_style.width+"\'; document.body.style.overflow = \''+origin_body_style.overflow+'\';document.body.removeChild(document.getElementById('starauction_img_container'));document.body.removeChild(document.getElementById('starauction_img_ifr'));})())");
	//	console.log(anchor.getAttribute('href'));
	//	div_cont.appendChild(result[j]);
		j++;
	}
	if(j > 300) {
		document.getElementById("katmary_img_container").innerHTML += '<div style="height: 74px; width: 490px; margin: 70px auto 0px; display: block; text-align: center; background-color: rgba(255, 255, 255, 0.4); border: 1px solid rgb(155, 155, 155); box-shadow: 0px 0px 4px 0px rgb(153, 153, 153);"><div style="font-family: tahoma; font-size: 16px; padding: 0px; margin-top: 10px; margin-bottom: 14px;">Подходящие изображения или видео на странице не найдены! </div><div style="margin: 0px auto; width: 466px;"><div style="background: url('+module_path+'/images/register_button.png) repeat scroll 0px 0px transparent; box-shadow: 1px 1px 2px -1px rgb(153, 153, 153); float: right; display: inline-block;"><a style="color: rgb(255, 255, 255); text-transform: uppercase; font-family: tahoma; font-size: 14px; font-weight: normal; text-decoration: none; width: 300px; display: block; padding: 1px 12px 2px;" href="javascript:void((function(){window.open(\''
								+params.new_window_params.url
								+"?img_src="
								+"&win_title="+encodeURIComponent(document.title.replace("'", '`'))
								+"&url="+encodeURIComponent(encodeURIComponent(location.href))
								+"&description="+encodeURIComponent(getDescription())
								+"&page_encoding="+encodeURIComponent(get_page_encodding())
								+"', '"+params.new_window_params.winName+"', '"
								+params.new_window_params.options
								+"');document.body.style.display = \'"+origin_body_style.display+"\'; document.body.style.width = \'"+origin_body_style.width+"\'; document.body.style.overflow = \''+origin_body_style.overflow+'\';document.body.removeChild(document.getElementById('starauction_img_container'));document.body.removeChild(document.getElementById('starauction_img_ifr'));})())\">продолжить без изображений и видео</a></div>"
								+'<div onClick="document.body.removeChild(document.getElementById(\'starauction_img_container\')); document.body.style.display = \''+origin_body_style.display+'\'; document.body.style.width = \''+origin_body_style.width+'\'; document.body.style.overflow = \''+origin_body_style.overflow+'\';document.body.removeChild(document.getElementById(\'starauction_img_ifr\'))" style="box-shadow: 1px 1px 2px -1px rgb(153, 153, 153); display: inline-block; float: left; cursor: pointer; font-size: 14px; font-weight: normal; background: url('+module_path+'/images/gradient_orange.jpg) repeat scroll 0px 0px transparent; text-transform: uppercase; color: rgb(255, 255, 255); padding: 2px 36px;">Отмена</div></div></div>'
		return false;
    }
// 	container.style.height = getHeight()+"px";
	window.scroll(0,0);
})();
