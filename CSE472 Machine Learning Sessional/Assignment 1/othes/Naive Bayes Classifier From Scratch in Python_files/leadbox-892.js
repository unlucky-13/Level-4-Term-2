;
(function(context) {

  var Patches = {
    String: {
      reverse: function() {
        return this.split("")
          .reverse()
          .join("");
      }
    },
    Array: {
      indexOf: function(obj, start) {
        for (var i = start || 0; i < this.length; i++)
          if (this[i] === obj)
            return i;
        return -1;
      }
    }
  };

  for (var key in Patches)(function() {
    var patch = Patches[key];
    var target = context[key];
    if (patch && target) {
      for (var method in patch) {
        if (!(method in target)) {
          target.prototype[method] = patch[method];
        }
      }
    }
  })();

})(this);

var safetyCheck = false;

function showFancyLeadboxes() {
  safetyCheck = true;
  console.log('We can safely display timed/exit leadboxes.');
}
(function() {
  var debugblock = window.location && String(window.location.hash) === '#debugblock';
  if (debugblock) {
    safetyCheck = false;
    return;
  }

  var safetyUrl = '//my.leadpages.net/static/all/js/can-i-show.js';
  var getSegment = function(url) {
    var segments = url.split('/');
    if (!~segments[0].indexOf('http')) {
      safetyUrl = '//' + segments[0] + '/static/all/js/can-i-show.js';
    } else {
      safetyUrl = '//' + segments[2] + '/static/all/js/can-i-show.js';
    }
    return safetyUrl;
  };
  if (document.currentScript) {
    safetyUrl = getSegment(document.currentScript.src);
  } else {
    var scripts = document.getElementsByTagName("script");
    for (var i = 0; i < scripts.length; i++) {
      var url = scripts[i].getAttribute('data-url');
      var match = url && url.match(/(.+\/)leadbox\/([0-9a-fA-F]+%3A[0-9a-fA-F]+)\/([0-9]+)\/$/);
      if (match) {
        safetyUrl = getSegment(url);
        break;
      }
    }
  }

  var script = document.createElement('script');
  script.src = safetyUrl;
  document.getElementsByTagName('head')[0].appendChild(script);
})();

;
(function() {

  if (window.LEADBOX) return;
  else window.LEADBOX = {};

  LEADBOX.debugging = window.location && String(window.location.hash) === '#debugging';

  // Utilities //

  function getSize(callback) {
    var body = window.document.body,
      doc = window.document.documentElement,
      documentWidth = Math.max(body.scrollWidth, doc.scrollWidth,
        body.offsetWidth, doc.offsetWidth,
        doc.clientWidth),
      documentHeight = Math.max(body.scrollHeight, doc.scrollHeight,
        body.offsetHeight, doc.offsetHeight,
        doc.clientHeight),
      viewportWidth = window.innerWidth || doc.clientWidth ||
      body.clientWidth,
      viewportHeight = window.innerHeight || doc.clientWidth ||
      body.clientWidth;

    // FB.Canvas may be defined because the host page is using the FB
    // JS API, but it will never trigger the callback because the page
    // is not hosted inside Facebook. As such, we give it 100ms to
    // trigger the callback, and if it doesn't, we'll just use the
    // default (non-facebook) values
    var workaround = window.setTimeout(function() {
      workaround = null;
      callback(documentWidth, documentHeight, viewportWidth,
        viewportHeight);
    }, 100);
    if (typeof FB != "undefined" && FB.Canvas) {
      FB.Canvas.getPageInfo(function(info) {
        if (workaround == null)
          return; // too late
        window.clearTimeout(workaround);
        workaround = null;

        if (info.clientWidth - info.offsetLeft < viewportWidth)
          viewportWidth = info.clientWidth - info.offsetLeft;
        if (info.clientHeight - info.offsetTop < viewportHeight)
          viewportHeight = info.clientHeight - info.offsetTop;
        callback(documentWidth, documentHeight, viewportWidth,
          viewportHeight);
      });
    }
  }

  function getScroll(callback) {
    var doc = document.documentElement,
      body = document.body,
      left = doc && doc.scrollLeft || body && body.scrollLeft || 0,
      top = doc && doc.scrollTop || body && body.scrollTop || 0;

    // FB.Canvas may be defined because the host page is using the FB
    // JS API, but it will never trigger the callback because the page
    // is not hosted inside Facebook. As such, we give it 100ms to
    // trigger the callback, and if it doesn't, we'll just use the
    // default (non-facebook) values
    var workaround = window.setTimeout(function() {
      workaround = null;
      callback(left, top, 0, 0);
    }, 100);

    if (typeof FB != "undefined" && FB.Canvas) {
      FB.Canvas.getPageInfo(function(info) {
        if (workaround == null)
          return; // too late
        window.clearTimeout(workaround);
        workaround = null;

        callback(left, top, info.scrollLeft, info.scrollTop);
      });
    }
  }

  function setScroll(left, top, fb_left, fb_top) {
    window.scrollTo(left, top);
    if (typeof FB != "undefined" && FB.Canvas) {
      FB.Canvas.scrollTo(fb_left, fb_top);
    }
  }

  function forEach(array, block, scope) {
    var set = array.slice(0);
    for (var i = 0, n = array.length; i < n; i++) {
      if (false === block.call(scope, set[i], i)) return false;
    }
    return true;
  }

  function addEvent(object, type, handler) {
    var method;
    if (object && type && handler) {
      method = object.addEventListener ? 'addEventListener' : object.attachEvent ? 'attachEvent' : '';
      type = method == 'addEventListener' ? type : 'on' + type;
      if (method) {
        object[method](type, function(event) {
          event = event ? event : window.event;
          handler.apply(object, [event]);
        });
        return true;
      }
    }
    return false;
  }

  function addInterval(block, delay) {
    var interval = {
      id: null,
      loop: null,
      delay: delay,
      block: block
    };
    interval.loop = function() {
      interval.block();
      interval.id = setTimeout(interval.loop, interval.delay);
      return interval;
    };
    return interval.loop();
  }

  function getIntersection(aStart, aEnd, bStart, bEnd) {

    var i = {};

    var aDelta = {
      x: aEnd.x - aStart.x,
      y: aEnd.y - aStart.y
    };

    var bDelta = {
      x: bEnd.x - bStart.x,
      y: bEnd.y - bStart.y
    };

    var s = (-aDelta.y * (aStart.x - bStart.x) + aDelta.x * (aStart.y - bStart.y)) / (-bDelta.x * aDelta.y + aDelta.x * bDelta.y);
    var t = (bDelta.x * (aStart.y - bStart.y) - bDelta.y * (aStart.x - bStart.x)) / (-bDelta.x * aDelta.y + aDelta.x * bDelta.y);


    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
      i.x = aStart.x + (t * aDelta.x);
      i.y = aStart.y + (t * aDelta.y);
      return i;
    }

    return null;
  }

  // Settings //

  var activating = null;
  var exitor = null;
  var MouseTracker = (function(debugging) {

    // get a handle on our environment

    var left = navigator.platform.match(/(Mac|iPhone|iPod|iPad)/i) ? 1 : 0;

    // define the button area location

    var buttonWidth = 350;
    var buttonHeight = 50;
    var chromeHeight = 0;

    // how far ahead to anticipate mouse movement
    var seconds = 1 / 4;

    // how sure to be they're going for the button
    var sureness = 1; // (0+)

    // account for user aim
    var userVariance = 150;

    var size = this.size = {
      x: null,
      y: null
    };
    var history = this.history = {
      x: null,
      y: null
    };
    var position = this.position = {
      x: null,
      y: null
    };
    var prediction = this.prediction = {
      x: null,
      y: null
    };
    var velocity = this.velocity = {
      x: 0,
      y: 0
    };

    var axis = {
      'x': 'y',
      'y': 'x'
    };
    var count = 0;
    var delay = 100;
    var sure = 0;
    var ready = false;
    var past = [];
    var back = 3;

    var canvas = document && document.documentElement ? document.documentElement : document.body;

    if (debugging) {
      document.documentElement.style.cursor = 'none';
      document.body.style.cursor = 'none';
    }

    function updateSize(event) {
      getSize(function(dw, dh, width, height) {
        size.x = width;
        size.y = height;
      });
    }

    function clearPosition(event) {
      position.x = null;
      position.y = null;
    }

    function updatePosition(event) {
      if (event) {
        position.x = event.clientX;
        position.y = event.clientY;
      }

      if (debugging) {
        var markers = document.getElementsByTagName('i');
        var marker = markers && markers[0] ? markers[0] : document.createElement('i');

        document.body.appendChild(marker);
        // if (!next.x && !next.y) document.body.removeChild(marker);

        marker.style.display = 'block';
        marker.style.position = 'fixed';
        marker.style.background = '#000';
        marker.style.width = '6px';
        marker.style.height = '6px';
        marker.style.marginLeft = '-3px';
        marker.style.marginTop = '-3px';
        marker.style.left = '' + position.x + 'px';
        marker.style.top = '' + position.y + 'px';
        marker.style.cursor = 'none';
        marker.style.zIndex = 101;
      }

    }

    function updateVector() {

      var anticipation = seconds * (1000 / delay);
      var projection = {
        x: position.x,
        y: position.y
      };

      for (var a in axis) {
        if (position[a] !== null) {
          velocity[a] = history[a] !== null ? position[a] - history[a] : 0;
          prediction[a] = position[a] + (velocity[a] * anticipation);
          history[a] = position[a];
        } else {
          history[a] = position[a] = prediction[a] = null;
        }
      }

      past = [{
        x: velocity.x,
        y: velocity.y
      }].concat(past.slice(0, back));

      var i = 0;
      var average = {
        x: 0,
        y: 0
      };
      forEach(past, function(value, key) {
        if (key < back) {
          average.x = average.x + value.x;
          average.y = average.y + value.y;
          i++;
        }
      });
      average.x = Math.round(average.x / i) * anticipation;
      average.y = Math.round(average.y / i) * anticipation;
      var next = {
        x: position.x + average.x,
        y: position.y + average.y
      };

      // show the predicted placement on the page

      if (debugging) {
        var markers = document.getElementsByTagName('var');
        var marker = markers && markers[0] ? markers[0] : document.createElement('var');

        document.body.appendChild(marker);
        if (!next.x && !next.y) document.body.removeChild(marker);

        marker.style.display = 'block';
        marker.style.position = 'fixed';
        marker.style.background = '#AAA';
        marker.style.width = '6px';
        marker.style.height = '6px';
        marker.style.marginLeft = '-3px';
        marker.style.marginTop = '-3px';
        marker.style.left = '' + next.x + 'px';
        marker.style.top = '' + next.y + 'px';
        marker.style.zIndex = 100;

      }

      // estimate if we are going for the close buttons

      getSize(function(dw, dh, vw, vh) {

        // left = false; // for debugging

        var closeStart = {
          x: left ? 0 - userVariance : vw - buttonWidth - userVariance,
          y: -1
        };
        var closeEnd = {
          x: left ? 0 + buttonWidth + userVariance : vw + userVariance,
          y: -1
        };

        var intersect = getIntersection(position, next, closeStart, closeEnd);

        if (intersect) {
          sure++;
          // console.log(sure, new Date)
          if (sure > sureness && !velocity.x && !velocity.y) {
            // if (window.LEADBOX.debugging && window.console && console.log) console.log('exit detected');
            if (exitor && safetyCheck) {
              window.LEADBOX.show(exitor);
              exitor = null;
            }
          }
        } else {
          sure = 0;
        }
      });

    };

    canvas.style.minHeight = '100%';

    // addEvent(canvas, 'mouseout', clearPosition); clearPosition();
    // addEvent(window, 'mouseout', clearPosition); clearPosition();
    addEvent(canvas, 'mousemove', updatePosition);
    updatePosition();
    addEvent(window, 'resize', updateSize);
    updateSize();

    addInterval(updateVector, 100);
  });

  var LeadBoxes = function() {

    var leadboxes = {};
    var background = document.createElement("div");

    background.style.position = "absolute";
    background.style.top = background.style.bottom =
      background.style.left = background.style.right = "0";
    background.style.zIndex = "2147483646";
    background.style.background = "black";
    background.style.width = "100%";
    background.style.opacity = "0.5";
    background.style.display = "none";
    document.body.appendChild(background);

    function init(id, url, stats) {
      var config = {};

      if (leadboxes[id]) return; // leadbox already initialized

      // We need to use this to track whether or not the LeadBox
      // was actually loaded through JS execution or not. This
      // is so we can prevent it from double tracking the view
      // event.
      if (url[url.length - 1] !== "&") {
        url += "&";
      }

      url += "__fromjs=1";

      if (typeof window.postMessage == "undefined" ||
        /Android|webOS|iPhone|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent)) {
        // mobile device or IE7-; redirect to form
        leadboxes[id] = [url, stats, config];
      } else {
        // desktop; open iframe in popup window
        leadboxes[id] = [document.createElement("iframe"), stats, config];
        leadboxes[id][0].src = url.replace("lp-in-iframe=0",
          "lp-in-iframe=1");
        leadboxes[id][0].style.position = "absolute";
        leadboxes[id][0].style.left = "0";
        leadboxes[id][0].style.top = "0";
        leadboxes[id][0].style.width = "100%";
        leadboxes[id][0].style.display = "none";
        leadboxes[id][0].style.border = "none";
        leadboxes[id][0].style.zIndex = "2147483647";

        leadboxes[id][0].onload = function() {
          if (window.LEADBOX.debugging) {
            if (window.console && console.log) console.log('resetting leadbox', id);
            leadboxes[id][0].contentWindow.postMessage({
              handler: 'reset',
              data: {
                id: id
              }
            }, '*');
          }
          var msg = JSON.stringify({
            handler: 'visit',
            visit: {
              id: id
            }
          })
          leadboxes[id][0].contentWindow.postMessage(msg, '*');
          leadboxes[id][0].onload = null;
        };

        document.body.appendChild(leadboxes[id][0]);

        getSize(function(documentWidth, documentHeight, width, height) {
          leadboxes[id][0].style.height = height + "px";
        });
      }
    }

    var active = null,
      overflow = null;

    // hides the most recently shown leadbox
    function hide() {
      if (!active) return;

      // hide frame
      leadboxes[active][0].style.display = "none";
      background.style.display = "none";
      active = null;

      // restore scroll position and scrolling settings
      document.body.style.overflow = overflow;
      overflow = null;
    }
    background.onclick = hide;

    // generates a v4 uuid
    function uuid() {
      return "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx".replace(/[xy]/g, function(c) {
        var r = ((new Date())
          .getTime() + Math.random() * 16) % 16 | 0;
        return (c == "x" ? r : (r & 0x7 | 0x8))
          .toString(16);
      });
    }

    // shows a leadbox by id; if another leadbox is currently shown, it is
    // hidden before proceeding
    function show(id, cb) {
      // call analytics
      var url = leadboxes[id][1] + "?",
        data = {
          "id": id,
          "uuid": uuid(),
          "type": "view",
          "served_by": "leadboxes"
        };
        try {
          leadboxes[id][0].contentWindow.postMessage({
            handler: 'display',
            display: {
              id: id
            }
          }, '*');
        } catch (e) {
          // the show must go on
        }

      for (var key in data) {
        if (data[key] !== undefined) {
          url += encodeURIComponent(key) + "=" +
            encodeURIComponent(data[key]) + "&";
        }
      }

      var image = document.createElement("img");
      if (typeof leadboxes[id][0] == "string") {
        // Replace fromjs=1 with fromjs=0 in order to force
        // view event tracking to happen on the backend in
        // cases where we open the leadbox in a new tab. This
        // is so that we track subsequent views as well should
        // the user re-visit the page later.
        var lbURL = leadboxes[id][0].replace("__fromjs=1", "__fromjs=0");

        // Open this LeadBox in a new tab. This is the
        // expected behavior on mobile devices.
        window.open(lbURL, "_blank");
      } else {
        getScroll(function(left, top, fbLeft, fbTop) {
          // hide previous leadbox, if any
          hide();

          // get scroll position and body overflow settings
          overflow = document.body.style.overflow;

          setScroll(left, top, fbLeft, fbTop);
          document.body.style.overflow = "hidden";

          // show leadbox and update active leadbox reference
          leadboxes[id][0].style.top = (top + fbTop) + "px";
          leadboxes[id][0].style.left = (left + fbLeft) + "px";
          leadboxes[id][0].style.display = "block";
          background.style.display = "block";
          active = id;
          if (cb) cb();

          // call analytics handler
          image.src = url;
        });
      }
    }

    // called when the leadbox should be resized
    this.resize = function() {
      getSize(function(documentWidth, documentHeight, width, height) {
        background.style.height = documentHeight + "px";
        for (var id in leadboxes) {
          if (typeof(leadboxes[id][0]) == "string")
            continue;
          leadboxes[id][0].style.height = height + "px";
        }
      });
    };

    var onMessageHandler = function(event) {
      if (event && event.data && event.data.handler) switch (event.data.handler) {
        case 'visited':
          // console.log('visited', event.data);
          var id = event.data.visit.id;
          var config = leadboxes[id][2] || {};
          var visit = event.data.visit;

          // console.log('visited ->', config, event.data.visit)

          var show = true;
          var day = 1000 * 60 * 60 * 24;
          var last = Number(new Date(visit['display-date'] || 0));
          var now = Number(new Date());



          var visits = visit['visit-count'] || 0;

          last = last ? last / day : 0;
          now = now / day;

          day = now - last;

          if (config.time) {
            var time = config.time;
            var timeout = (time.seconds * 1000) || 0;

            show = true;

            if (time.views) show = show && !(visits % (time.views + 1));
            if (time.days) show = show && time.days < day;
            if (show) setTimeout(function() {
              if (safetyCheck) {
                window.LEADBOX.show(id);
              }
            }, timeout);
          }
          if (config.exit) {
            var exit = config.exit;
            show = true;
            if (exit.days) show = show && exit.days < day;
            if (show) exitor = id;
            // console.log('exit', config.exit, new Date(visit['display-date']));
          }
          break;
        case 'displayed':
          break;
      }
      if (event.data == "close") hide();
    };

    // prep leadboxes
    var scripts = document.getElementsByTagName("script");
    var triggers = document.getElementsByTagName("a"),
      callback = function(event) {
        var attr = this.getAttribute("data-leadbox");
        if (attr) {
          if (event && event.preventDefault) event.preventDefault();
          show(attr);
        }
        return false;
      };

    for (var i = 0; i < triggers.length; i++) {
      try {
        (function() {
          var id;
          var trigger = triggers[i];
          var url = trigger.getAttribute("href");
          var match = url.split("?")[0].match(/(.+\/)leadbox\/([0-9a-fA-F]+%3A[0-9a-fA-F]+)\/([0-9]+)\/$/);  // allow for "?uriparm=urival&etc=etc" suffix too

          if (match) {

            id = match[2] = decodeURIComponent(match[2]);
            init(id, // form-id
              url + // iframe url
              ((url.indexOf("?") == -1) ? "?" : "&") + // query separator
              "lp-in-iframe=0&" + // position fix
              window.location.search.replace(/^\?/, ""), // prepopulation
              match[1] + "forms/pixel/" + match[3] + "/"); // analytics url
            trigger.setAttribute("data-leadbox", id);
            trigger.onclick = callback;
          }

        })();
      } catch (e) {
        // show must go on
      }
    }

    for (var i = 0; i < scripts.length; i++) {
      (function(script) {
        var id = script.getAttribute('data-leadbox');
        var url = script.getAttribute('data-url');
        var match = url && url.match(/(.+\/)leadbox\/([0-9a-fA-F]+%3A[0-9a-fA-F]+)\/([0-9]+)\/$/);
        var config = script.getAttribute('data-config');
        config = config && JSON && JSON.parse(unescape(config));

        if (match) {
          var formUrl = url + // iframe url
            ((url.indexOf("?") == -1) ? "?" : "&") + // query separator
            "lp-in-iframe=0&" + // position fix
            window.location.search.replace(/^\?/, ""); // prepopulation
          var statUrl = match[1] + "forms/pixel/" + match[3] + "/";

          init(id, formUrl, statUrl);

          if (config && config.type) {
            // console.log(id, config, leadboxes[id]);
            var settings = leadboxes[id][2] = leadboxes[id] ? leadboxes[id][2] : {};
            settings[config.type] = config.settings;
            // console.log(leadboxes[id]);
          }

        }

      })(scripts[i]);
    }

    // setup leadbox close handlers
    window.formFrameClosed = hide;

    // setup leadbox window handlers
    addEvent(window, 'message', onMessageHandler);

    // start mouse tracking if exitor has been set
    // console.log('MouseTracker', exitor, window.LEADBOX.debugging)
    // setTimeout(function(){ new MouseTracker(window.LEADBOX.debugging) });
    setTimeout(function() {
      new MouseTracker()
    });

    // public controller
    window.LEADBOX.reset = function(id) {
      var key;
      for (key in leadboxes) {};
      if (leadboxes && leadboxes[key]) {
        leadboxes[key][0].contentWindow.postMessage({
          'handler': 'reset',
          'data': {
            id: id
          }
        }, '*');
      }
    };
    window.LEADBOX.show = function(id) {
      // console.log('show?', id)
      if (id && activating !== id && active !== id) {
        activating = id;
        // console.log('post')
        leadboxes[id][0].contentWindow.postMessage({
          handler: 'display',
          display: {
            id: id
          }
        }, '*');
        show(id, function() {
          activating = null;
          // console.log('shown.', id);
        });
      }
    };
    window.LEADBOX.hide = function() {
      hide();
    };

    if (window.LEADBOX && window.LEADBOX.debugging) {
      if (window.console && console.log) console.log('debugging detected, resetting active leadboxes');
      // window.location.hash = 'debugged';
    }

  };

  var load = function() {
    if (!window.ae417310535411e38f960800200c9a66)
      window.ae417310535411e38f960800200c9a66 = new LeadBoxes();
    window.ae417310535411e38f960800200c9a66.resize();
  };

  // bind to 'load' and 'resize' (standards)
  if (window.addEventListener) {
    window.addEventListener("load", load);
    window.addEventListener("resize", load);
    // speed-up load where possible
    document.addEventListener("DOMContentLoaded", load);
  }
  // tender love & care for internet explorer
  else if (window.attachEvent) {
    window.attachEvent("onload", load);
    window.attachEvent("onresize", load);
    // speed up load event
    document.attachEvent("onreadystatechange", function() {
      if (document.readyState === "complete")
        load();
    });
  } else {
    var oldLoad = window.onload,
      oldResize = window.onresize;
    window.onload = function() {
      load();
      if (typeof oldLoad == "function")
        oldLoad();
    };
    window.onresize = function(e) {
      load();
      if (typeof oldResize == "function")
        oldResize(e);
    };
  }
})();
