(function() {
  var Client,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; };

  Client = (function() {

    Client.prototype.server_address = null;

    Client.prototype.port = null;

    Client.prototype.grid = null;

    Client.prototype.cellSize = 10;

    Client.prototype.numberOfRows = 50;

    Client.prototype.numberOfColumns = 50;

    Client.prototype.updateLength = 100;

    Client.prototype.canvas = null;

    Client.prototype.drawingCanvas = null;

    function Client(server_address, port) {
      this.server_address = server_address;
      this.port = port;
      this.update = __bind(this.update, this);
      this.removeForm();
      this.createCanvas();
      this.resizeCanvas();
      this.createDrawingContext();
      this.initialize();
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

    Client.prototype.initialize = function() {
      var column, row, _ref, _results;
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
      this.server_address = document.querySelectorAll('input[name="input1"]')[0].value;
      this.port = document.querySelectorAll('input[name="input2"]')[0].value;
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

  window.Client = Client;

}).call(this);
