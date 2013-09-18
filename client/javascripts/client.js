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

    function Client() {
      this.update = __bind(this.update, this);      this.removeForm();
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
          var str2ab;
          str2ab = function(str) {
            var buf, bufView, i, _ref;
            buf = new ArrayBuffer(str.length);
            bufView = new Uint8Array(buf);
            for (i = 0, _ref = str.length; 0 <= _ref ? i < _ref : i > _ref; 0 <= _ref ? i++ : i--) {
              bufView[i] = str.charCodeAt(i);
            }
            return buf;
          };
          return socket.write(_this.socket_info.socketId, str2ab("HELLO\n"), function(writeInfo) {
            return console.debug("writeinfo", writeInfo);
          });
        });
      });
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

    Client.prototype.update = function() {
      if (this.socket_info === null) {
        console.debug("NULL");
      } else {
        chrome.socket.read(this.socket_info.socketId, function(readInfo) {
          var ab2str;
          console.debug("Reading...");
          if (readInfo.resultCode > 0) {
            ab2str = function(ab) {
              return String.fromCharCode.apply(null, new Uint8Array(ab));
            };
            return console.debug(ab2str(readInfo.data));
          }
        });
      }
      this.drawGrid();
      return setTimeout(this.update, this.updateLength);
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
      var fillStyle, x, y;
      x = cell.column * this.cellSize;
      y = cell.row * this.cellSize;
      if (cell.occupancy.length === 0) fillStyle = 'rgb(38, 38, 38)';
      if (cell.row === parseInt(this.port, 10) && cell.column === parseInt(this.server_address, 10)) {
        fillStyle = 'rgb(242, 198, 65)';
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
