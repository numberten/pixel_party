class Client
  server_address: null
  port: null
  grid: null
  cellSize: 10
  numberOfRows: 50
  numberOfColumns: 50
  updateLength: 100
  canvas: null
  drawingCanvas: null

  #Constructor
  constructor: (@server_address, @port) ->
    @removeForm()

    @createCanvas()
    @resizeCanvas()
    @createDrawingContext()

    #    @joinServer()
    @initialize()

    @update()

  createCanvas: ->
    @canvas = document.createElement 'canvas'
    document.body.appendChild @canvas

  resizeCanvas: ->
    @canvas.height  = @cellSize * @numberOfRows
    @canvas.width   = @cellSize * @numberOfColumns

  createDrawingContext: ->
    @drawingContext = @canvas.getContext '2d'

  #Hide 'server_info' form
  removeForm: ->
    document.getElementById("server_info").style.display="none"

  #Join the server
  #joinServer: ->

  initialize: ->

    @grid = []

    for row in [0...@numberOfRows]
      @grid[row] = []
      for column in [0...@numberOfColumns]
        @grid[row][column] = @createInitialCell row, column

  createInitialCell: (row, column) ->
    occupancy: []
    row: row
    column: column

  #Update function
  update: =>
    @server_address = document.querySelectorAll('input[name="input1"]')[0].value
    @port = document.querySelectorAll('input[name="input2"]')[0].value
    #{TODO} Read packets from server.
    @drawGrid()

    setTimeout @update, @updateLength

  drawGrid: ->
    for row in [0...@numberOfRows]
      for column in [0...@numberOfColumns]
        @drawCell @grid[row][column]

  drawCell: (cell) ->
    x = cell.column * @cellSize
    y = cell.row * @cellSize

    if cell.occupancy.length is 0
      fillStyle = 'rgb(38, 38, 38)'
    if cell.row is parseInt(@server_address, 10) and cell.column is parseInt(@port, 10)
      fillStyle = 'rgb(242, 198, 65)'
    #else
      #Fill based on occupancy list
    
    @drawingContext.strokeStyle = 'rgba(242, 198, 65, 0.1)'
    @drawingContext.strokeRect x, y, @cellSize, @cellSize

    @drawingContext.fillStyle = fillStyle
    @drawingContext.fillRect x, y, @cellSize, @cellSize

window.Client = Client
