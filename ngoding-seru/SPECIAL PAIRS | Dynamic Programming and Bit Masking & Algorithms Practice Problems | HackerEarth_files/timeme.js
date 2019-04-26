(function () {
    ! function (e, t) {
        "undefined" != typeof module && module.exports ? module.exports = t() : "function" == typeof define && define.amd ? define([], function () {
            return e.TimeMe = t()
        }) : e.TimeMe = t()
    }(this, function () {
        var e = {
            startStopTimes: {},
            idleTimeoutMs: 3e4,
            currentIdleTimeMs: 0,
            checkStateRateMs: 250,
            active: !1,
            idle: !1,
            currentPageName: "default-page-name",
            timeElapsedCallbacks: [],
            userLeftCallbacks: [],
            userReturnCallbacks: [],
            trackTimeOnElement: function (t) {
                var n = document.getElementById(t);
                n && (n.addEventListener("mouseover", function () {
                    e.startTimer(t)
                }), n.addEventListener("mousemove", function () {
                    e.startTimer(t)
                }), n.addEventListener("mouseleave", function () {
                    e.stopTimer(t)
                }), n.addEventListener("keypress", function () {
                    e.startTimer(t)
                }), n.addEventListener("focus", function () {
                    e.startTimer(t)
                }))
            },
            getTimeOnElementInSeconds: function (t) {
                var n = e.getTimeOnPageInSeconds(t);
                return n || 0
            },
            startTimer: function (t) {
                if (t || (t = e.currentPageName), void 0 === e.startStopTimes[t]) e.startStopTimes[t] = [];
                else {
                    var n = e.startStopTimes[t],
                        i = n[n.length - 1];
                    if (void 0 !== i && void 0 === i.stopTime) return
                }
                e.startStopTimes[t].push({
                    startTime: new Date,
                    stopTime: void 0
                }), e.active = !0
            },
            stopAllTimers: function () {
                for (var t = Object.keys(e.startStopTimes), n = 0; n < t.length; n++) e.stopTimer(t[n])
            },
            stopTimer: function (t) {
                t || (t = e.currentPageName);
                var n = e.startStopTimes[t];
                void 0 !== n && 0 !== n.length && (void 0 === n[n.length - 1].stopTime && (n[n.length - 1].stopTime = new Date), e.active = !1)
            },
            getTimeOnCurrentPageInSeconds: function () {
                return e.getTimeOnPageInSeconds(e.currentPageName)
            },
            getTimeOnPageInSeconds: function (t) {
                return void 0 === e.getTimeOnPageInMilliseconds(t) ? void 0 : e.getTimeOnPageInMilliseconds(t) / 1e3
            },
            getTimeOnCurrentPageInMilliseconds: function () {
                return e.getTimeOnPageInMilliseconds(e.currentPageName)
            },
            getTimeOnPageInMilliseconds: function (t) {
                var n = e.startStopTimes[t];
                if (void 0 !== n) {
                    for (var i = 0, s = 0; s < n.length; s++) {
                        var o = n[s].startTime,
                            r = n[s].stopTime;
                        void 0 === r && (r = new Date), i += r - o
                    }
                    return Number(i)
                }
            },
            getTimeOnAllPagesInSeconds: function () {
                for (var t = [], n = Object.keys(e.startStopTimes), i = 0; i < n.length; i++) {
                    var s = n[i],
                        o = e.getTimeOnPageInSeconds(s);
                    t.push({
                        pageName: s,
                        timeOnPage: o
                    })
                }
                return t
            },
            setIdleDurationInSeconds: function (t) {
                var n = parseFloat(t);
                if (!1 !== isNaN(n)) throw {
                    name: "InvalidDurationException",
                    message: "An invalid duration time (" + t + ") was provided."
                };
                return e.idleTimeoutMs = 1e3 * t, this
            },
            setCurrentPageName: function (t) {
                return e.currentPageName = t, this
            },
            resetRecordedPageTime: function (t) {
                delete e.startStopTimes[t]
            },
            resetAllRecordedPageTimes: function () {
                for (var t = Object.keys(e.startStopTimes), n = 0; n < t.length; n++) e.resetRecordedPageTime(t[n])
            },
            resetIdleCountdown: function () {
                e.idle && e.triggerUserHasReturned(), e.idle = !1, e.currentIdleTimeMs = 0
            },
            callWhenUserLeaves: function (e, t) {
                this.userLeftCallbacks.push({
                    callback: e,
                    numberOfTimesToInvoke: t
                })
            },
            callWhenUserReturns: function (e, t) {
                this.userReturnCallbacks.push({
                    callback: e,
                    numberOfTimesToInvoke: t
                })
            },
            triggerUserHasReturned: function () {
                if (!e.active)
                    for (var t = 0; t < this.userReturnCallbacks.length; t++) {
                        var n = this.userReturnCallbacks[t],
                            i = n.numberOfTimesToInvoke;
                        (isNaN(i) || void 0 === i || i > 0) && (n.numberOfTimesToInvoke -= 1, n.callback())
                    }
                e.startTimer()
            },
            triggerUserHasLeftPage: function () {
                if (e.active)
                    for (var t = 0; t < this.userLeftCallbacks.length; t++) {
                        var n = this.userLeftCallbacks[t],
                            i = n.numberOfTimesToInvoke;
                        (isNaN(i) || void 0 === i || i > 0) && (n.numberOfTimesToInvoke -= 1, n.callback())
                    }
                e.stopAllTimers()
            },
            callAfterTimeElapsedInSeconds: function (t, n) {
                e.timeElapsedCallbacks.push({
                    timeInSeconds: t,
                    callback: n,
                    pending: !0
                })
            },
            checkState: function () {
                for (var t = 0; t < e.timeElapsedCallbacks.length; t++) e.timeElapsedCallbacks[t].pending && e.getTimeOnCurrentPageInSeconds() > e.timeElapsedCallbacks[t].timeInSeconds && (e.timeElapsedCallbacks[t].callback(), e.timeElapsedCallbacks[t].pending = !1);
                !1 === e.idle && e.currentIdleTimeMs > e.idleTimeoutMs ? (e.idle = !0, e.triggerUserHasLeftPage()) : e.currentIdleTimeMs += e.checkStateRateMs
            },
            visibilityChangeEventName: void 0,
            hiddenPropName: void 0,
            listenForVisibilityEvents: function () {
                void 0 !== document.hidden ? (e.hiddenPropName = "hidden", e.visibilityChangeEventName = "visibilitychange") : void 0 !== document.mozHidden ? (e.hiddenPropName = "mozHidden", e.visibilityChangeEventName = "mozvisibilitychange") : void 0 !== document.msHidden ? (e.hiddenPropName = "msHidden", e.visibilityChangeEventName = "msvisibilitychange") : void 0 !== document.webkitHidden && (e.hiddenPropName = "webkitHidden", e.visibilityChangeEventName = "webkitvisibilitychange"), document.addEventListener(e.visibilityChangeEventName, function () {
                    document[e.hiddenPropName] ? e.triggerUserHasLeftPage() : e.triggerUserHasReturned()
                }, !1), window.addEventListener("blur", function () {
                    e.triggerUserHasLeftPage()
                }), window.addEventListener("focus", function () {
                    e.triggerUserHasReturned()
                }), document.addEventListener("mousemove", function () {
                    e.resetIdleCountdown()
                }), document.addEventListener("keyup", function () {
                    e.resetIdleCountdown()
                }), document.addEventListener("touchstart", function () {
                    e.resetIdleCountdown()
                }), window.addEventListener("scroll", function () {
                    e.resetIdleCountdown()
                }), setInterval(function () {
                    e.checkState()
                }, e.checkStateRateMs)
            },
            websocket: void 0,
            websocketHost: void 0,
            setUpWebsocket: function (t) {
                if (window.WebSocket && t) {
                    var n = t.websocketHost;
                    try {
                        e.websocket = new WebSocket(n), window.onbeforeunload = function (n) {
                            e.sendCurrentTime(t.appId)
                        }, e.websocket.onopen = function () {
                            e.sendInitWsRequest(t.appId)
                        }, e.websocket.onerror = function (e) {
                            console && console.log("Error occurred in websocket connection: " + e)
                        }, e.websocket.onmessage = function (e) {
                            console && console.log(e.data)
                        }
                    } catch (e) {
                        console && console.error("Failed to connect to websocket host.  Error:" + e)
                    }
                }
                return this
            },
            websocketSend: function (t) {
                e.websocket.send(JSON.stringify(t))
            },
            sendCurrentTime: function (t) {
                var n = {
                    type: "INSERT_TIME",
                    appId: t,
                    timeOnPageMs: e.getTimeOnCurrentPageInMilliseconds(),
                    pageName: e.currentPageName
                };
                e.websocketSend(n)
            },
            sendInitWsRequest: function (t) {
                var n = {
                    type: "INIT",
                    appId: t
                };
                e.websocketSend(n)
            },
            initialize: function (t) {
                var n = e.idleTimeoutMs || 30,
                    i = e.currentPageName || "default-page-name",
                    s = void 0;
                t && (n = t.idleTimeoutInSeconds || n, i = t.currentPageName || i, s = t.websocketOptions), e.setIdleDurationInSeconds(n).setCurrentPageName(i).setUpWebsocket(s).listenForVisibilityEvents(), e.startTimer()
            }
        };
        return e
    })
})(window);

