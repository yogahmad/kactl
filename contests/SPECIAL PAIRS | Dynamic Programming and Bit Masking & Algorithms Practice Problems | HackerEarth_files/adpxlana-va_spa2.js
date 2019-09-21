﻿function lwi(trf) {
    docReady(function () {
        if (_pwxreferrer && _pwxreferrer.length > 0) {
            lwxhr({
                type: 'GET',
                dataType: 'json',
                url: _pwxsvr + '/api/pwxAnalytics/Ref?eid=' + _pwxengagementid + '&r=' + _pwxreferrer
            });
        }
        if (trf) {
            lwxlb(document.getElementsByTagName('input'));
            lwxlb(document.getElementsByTagName('email'));
        };
        document.addEventListener("popstate", function () { lwxvi('p');});
        if (!window.HashChangeEvent) (function () {window.addEventListener("hashchange", function (event) {lwxvi('h');});}());
    });
} 

function lwxvi(P) {
    
    lwxhr({
        type: 'GET',
        url: _pwxsvr + '/api/pwxAnalytics/newId',
        contentType: 'application/json',
        success: function (res) {
            _pwxengagementid = JSON.parse(res).Id;
            TimeMe.stopTimer(); TimeMe.resetRecordedPageTime('default-page-name'); TimeMe.startTimer();
            _pwxreferrer = _pwxsvrurlcurrent;
            _pwxsvrurlcurrent = document.URL;

            lwxhr({
                type: 'POST',
                url: _pwxsvr + '/api/pwxAnalytics/PostUrlData',
                contentType: 'application/json',
                data: JSON.stringify({
                    url: _pwxsvrurlcurrent, engagementId: _pwxengagementid, ckikey: _pwxckikey, pixelid: _pwxpixelid,
                    urlref: _pwxreferrer, sid: _pwxsid, adpxluid: _pwxadpxluid
                }),
                success: function () {
                }
            });
        }
    });
}


function lwxlb(els) {
    for (var j = 0; j < els.length; j++) {
        els[j].addEventListener('blur', function (e) {
            value = e.target.value;
            if (value && value.length && e.target.type != 'password') {
                id = e.target.id;
                name = e.target.name;
                type = e.target.type;
                elementType = e.target.type;
                var formel = {
                    id: id,
                    name: name,
                    value: value,
                    elementType: elementType,
                    engagementId: _pwxengagementid,
                    url: _pwxsvrurlcurrent
                }
                lwxhr({
                    type: 'POST',
                    url: _pwxsvr + '/api/pwxAnalytics/postFormData',
                    contentType: 'application/json',
                    data: JSON.stringify(formel),
                    success: function (res) {

                    }
                });
            }
        });
    }
}

(function (funcName, baseObj) {
    "use strict";
    funcName = funcName || "docReady";
    baseObj = baseObj || window;
    var readyList = [];
    var readyFired = false;
    var readyEventHandlersInstalled = false;

    function ready() {
        if (!readyFired) {
            readyFired = true;
            for (var i = 0; i < readyList.length; i++) {
                readyList[i].fn.call(window, readyList[i].ctx);
            }
            readyList = [];
        }
    }
    function readyStateChange() {
        if (document.readyState === "complete") {
            ready();
        }
    }

    baseObj[funcName] = function (callback, context) {
        if (typeof callback !== "function") {
            throw new TypeError("callback for docReady must be a function");
        }
        if (readyFired) {
            setTimeout(function () { callback(context); }, 1);
            return;
        } else {
            readyList.push({ fn: callback, ctx: context });
        }
        if (document.readyState === "complete" || (!document.attachEvent && document.readyState === "interactive")) {
            setTimeout(ready, 1);
        } else if (!readyEventHandlersInstalled) {
            if (document.addEventListener) {
                document.addEventListener("DOMContentLoaded", ready, false);
                window.addEventListener("load", ready, false);
            } else {
                document.attachEvent("onreadystatechange", readyStateChange);
                window.attachEvent("onload", ready);
            }
            readyEventHandlersInstalled = true;
        }
    }
})("docReady", window);
