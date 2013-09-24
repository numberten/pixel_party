(function() {
  var Client, client_spawner, main,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; };

  Client = (function() {

    Client.prototype.socket_info = null;

    Client.prototype.server_address = "test";

    Client.prototype.port = null;

    Client.prototype.grid = null;

    Client.prototype.cellSize = 10;

    Client.prototype.numberOfRows = 50;

    Client.prototype.numberOfColumns = 50;

    Client.prototype.updateLength = 100;

    Client.prototype.canvas = null;

    Client.prototype.drawingCanvas = null;

    Client.prototype.myPixel = {
      x: null,
      y: null,
      red: null,
      green: null,
      blue: null
    };

    function Client() {
      this.react = __bind(this.react, this);
      this.update = __bind(this.update, this);
      this.addPixel = __bind(this.addPixel, this);
      this.joinServer = __bind(this.joinServer, this);      this.removeForm();
      this.createCanvas();
      this.resizeCanvas();
      this.createDrawingContext();
      this.initialize();
      this.joinServer();
      this.update();
    }

    Client.prototype.createCanvas = function() {
      this.canvas = document.createElement('canvas');
      return document.body.appendChild(this.canvas);
    };

    Client.prototype.resizeCanvas = function() {
      this.canvas.height = this.cellSize * this.numberOfRows;
      return this.canvas.width = this.cellSize * this.numberOfColumns;
    };

    Client.prototype.createDrawingContext = function() {
      return this.drawingContext = this.canvas.getContext('2d');
    };

    Client.prototype.removeForm = function() {
      return document.getElementById("server_info").style.display = "none";
    };

    Client.prototype.joinServer = function() {
      var socket,
        _this = this;
      socket = chrome.socket;
      return socket.create('udp', {}, function(socketInfo) {
        _this.socket_info = socketInfo;
        return socket.connect(_this.socket_info.socketId, _this.server_address, _this.port, function(connectResult) {
          return socket.write(_this.socket_info.socketId, _this.str2ab("HELLO\n"), function(writeInfo) {
            return console.debug("writeinfo", writeInfo);
          });
        });
      });
    };

    Client.prototype.str2ab = function(str) {
      var buf, bufView, i, _ref;
      buf = new ArrayBuffer(str.length);
      bufView = new Uint8Array(buf);
      for (i = 0, _ref = str.length; 0 <= _ref ? i < _ref : i > _ref; 0 <= _ref ? i++ : i--) {
        bufView[i] = str.charCodeAt(i);
      }
      return buf;
    };

    Client.prototype.initialize = function() {
      var column, row, _ref, _results;
      this.server_address = document.querySelectorAll('input[name="input1"]')[0].value.toString();
      this.port = parseInt(document.querySelectorAll('input[name="input2"]')[0].value, 10);
      this.grid = [];
      _results = [];
      for (row = 0, _ref = this.numberOfRows; 0 <= _ref ? row < _ref : row > _ref; 0 <= _ref ? row++ : row--) {
        this.grid[row] = [];
        _results.push((function() {
          var _ref2, _results2;
          _results2 = [];
          for (column = 0, _ref2 = this.numberOfColumns; 0 <= _ref2 ? column < _ref2 : column > _ref2; 0 <= _ref2 ? column++ : column--) {
            _results2.push(this.grid[row][column] = this.createInitialCell(row, column));
          }
          return _results2;
        }).call(this));
      }
      return _results;
    };

    Client.prototype.createInitialCell = function(row, column) {
      return {
        occupancy: [],
        row: row,
        column: column
      };
    };

    Client.prototype.addPixel = function(x, y, r, g, b) {
      return this.grid[x][y].occupancy.push({
        red: r,
        green: g,
        blue: b
      });
    };

    Client.prototype.update = function() {
      var _this = this;
      if (this.socket_info != null) {
        chrome.socket.read(this.socket_info.socketId, function(readInfo) {
          var ab2str;
          console.debug("Reading...");
          if (readInfo.resultCode > 0) {
            ab2str = function(ab) {
              return String.fromCharCode.apply(null, new Uint8Array(ab));
            };
            return _this.react(ab2str(readInfo.data));
          }
        });
      }
      this.drawGrid();
      return setTimeout(this.update, this.updateLength);
    };

    Client.prototype.react = function(str) {
      var column, deepEquals, m, p, row, _ref, _results;
      console.debug(str);
      if (str.match(/^PING/)) {
        console.debug("CAUGHT PING");
        return chrome.socket.write(this.socket_info.socketId, this.str2ab("PONG\n"), function(writeInfo) {
          return console.debug("writeinfo", writeInfo);
        });
      }
      m = /^WELCOME: x:(\d+),y:(\d+),r:(\d+),g:(\d+),b:(\d+)/.exec(str);
      if (m != null) {
        console.debug("CAUGHT WELCOME");
        m = m.map(function(i) {
          return parseInt(i, 10);
        });
        return this.myPixel = {
          x: m[1],
          y: m[2],
          red: m[3],
          green: m[4],
          blue: m[5]
        };
      }
      m = /(\d+),(\d+),(\d+),(\d+),(\d+)\$/.exec(str);
      if (m != null) {
        console.debug("m:", m);
        console.debug("CAUGHT pixeldata$");
        console.debug("m[1]: " + m[1] + " m[2]: " + m[2]);
        m = m.map(function(i) {
          return parseInt(i, 10);
        });
        console.debug("m[1]: " + m[1] + " m[2]: " + m[2]);
        _results = [];
        for (row = 0, _ref = this.numberOfRows; 0 <= _ref ? row < _ref : row > _ref; 0 <= _ref ? row++ : row--) {
          _results.push((function() {
            var _ref2, _results2;
            _results2 = [];
            for (column = 0, _ref2 = this.numberOfColumns; 0 <= _ref2 ? column < _ref2 : column > _ref2; 0 <= _ref2 ? column++ : column--) {
              deepEquals = function(list1, list2) {
                var i, _ref3;
                if (list1.length !== list2.length) return false;
                for (i = 0, _ref3 = list1.length; 0 <= _ref3 ? i < _ref3 : i > _ref3; 0 <= _ref3 ? i++ : i--) {
                  if (list1[i] !== list2[i]) return false;
                }
                return true;
              };
              this.grid[row][column].occupancy = (function() {
                var _i, _len, _ref3, _results3;
                _ref3 = this.grid[row][column].occupancy;
                _results3 = [];
                for (_i = 0, _len = _ref3.length; _i < _len; _i++) {
                  p = _ref3[_i];
                  if (!deepEquals([p.red, p.green, p.blue], [m[3], m[4], m[5]])) {
                    _results3.push(p);
                  }
                }
                return _results3;
              }).call(this);
              if (deepEquals([row, column], [m[2], m[1]])) {
                console.log("Equality 4 all!");
                _results2.push(this.grid[row][column].occupancy.push({
                  red: m[3],
                  green: m[4],
                  blue: m[5]
                }));
              } else {
                _results2.push(void 0);
              }
            }
            return _results2;
          }).call(this));
        }
        return _results;
      }
    };

    Client.prototype.drawGrid = function() {
      var column, row, _ref, _results;
      _results = [];
      for (row = 0, _ref = this.numberOfRows; 0 <= _ref ? row < _ref : row > _ref; 0 <= _ref ? row++ : row--) {
        _results.push((function() {
          var _ref2, _results2;
          _results2 = [];
          for (column = 0, _ref2 = this.numberOfColumns; 0 <= _ref2 ? column < _ref2 : column > _ref2; 0 <= _ref2 ? column++ : column--) {
            _results2.push(this.drawCell(this.grid[row][column]));
          }
          return _results2;
        }).call(this));
      }
      return _results;
    };

    Client.prototype.drawCell = function(cell) {
      var b, fillStyle, g, p, r, x, y, _i, _len, _ref, _ref2, _ref3, _ref4;
      x = cell.column * this.cellSize;
      y = cell.row * this.cellSize;
      if (cell.occupancy.length === 0) {
        fillStyle = 'rgb(38, 38, 38)';
      } else {
        _ref = [0, 0, 0], r = _ref[0], g = _ref[1], b = _ref[2];
        _ref2 = cell.occupancy;
        for (_i = 0, _len = _ref2.length; _i < _len; _i++) {
          p = _ref2[_i];
          _ref3 = [r + p.red, g + p.green, b + p.blue], r = _ref3[0], g = _ref3[1], b = _ref3[2];
        }
        _ref4 = [r / cell.occupancy.length, g / cell.occupancy.length, b / cell.occupancy.length], r = _ref4[0], g = _ref4[1], b = _ref4[2];
        fillStyle = "rgb(" + r + ", " + g + ", " + b + ")";
        console.log(fillStyle);
      }
      this.drawingContext.strokeStyle = 'rgba(242, 198, 65, 0.1)';
      this.drawingContext.strokeRect(x, y, this.cellSize, this.cellSize);
      this.drawingContext.fillStyle = fillStyle;
      return this.drawingContext.fillRect(x, y, this.cellSize, this.cellSize);
    };

    return Client;

  })();

  main = function() {
    return chrome.app.runtime.onLaunched.addListener(function() {
      return chrome.app.window.create("../index.html", {
        bounds: {
          width: 400,
          height: 500
        }
      });
    });
  };

  client_spawner = function() {
    return new Client;
  };

  document.addEventListener("DOMContentLoaded", function() {
    var _ref;
    main();
    return (_ref = document.querySelector("input[name=\"button\"]")) != null ? _ref.addEventListener("click", client_spawner) : void 0;
  });

}).call(this);
