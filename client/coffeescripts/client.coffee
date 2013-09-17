class Client
  socket_info: null
  server_address: "test"
  port: null
  grid: null
  cellSize: 10
  numberOfRows: 50
  numberOfColumns: 50
  updateLength: 100
  canvas: null
  drawingCanvas: null

  #Constructor
  constructor: ->
    @removeForm()

    @createCanvas()
    @resizeCanvas()
    @createDrawingContext()

    @initialize()
    @joinServer()

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

  joinServer: ->
    socket = chrome.socket
    socket.create 'udp', {}, (socketInfo) =>
      @socket_info = socketInfo
      socket.connect @socket_info.socketId, @server_address, @port, (connectResult) =>

        # str2ab: Takes a string and turns it into an arraybuffer.
        #   ArrayBuffer takes the number of bytes to allocate.
        #   ArrayBuffers must be accessed via a DataView. In this case a Uint8Array.

        str2ab = (str) ->
          buf = new ArrayBuffer(str.length)
          bufView = new Uint8Array(buf)
          bufView[i] = str.charCodeAt(i) for i in [0...str.length]
          buf
        socket.write @socket_info.socketId, str2ab("HELLO\n"), (writeInfo) ->
          console.debug "writeinfo", writeInfo

  initialize: ->
    @server_address = document.querySelectorAll('input[name="input1"]')[0].value.toString()
    @port = parseInt(document.querySelectorAll('input[name="input2"]')[0].value, 10)
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
    if cell.row is parseInt(@port, 10) and cell.column is parseInt(@server_address, 10)
      fillStyle = 'rgb(242, 198, 65)'
    #else
      #Fill based on occupancy list
    
    @drawingContext.strokeStyle = 'rgba(242, 198, 65, 0.1)'
    @drawingContext.strokeRect x, y, @cellSize, @cellSize

    @drawingContext.fillStyle = fillStyle
    @drawingContext.fillRect x, y, @cellSize, @cellSize

main = ->
  chrome.app.runtime.onLaunched.addListener ->
    chrome.app.window.create "../index.html",
      bounds:
        width: 400
        height: 500

client_spawner = ->
  new Client

document.addEventListener "DOMContentLoaded", ->
  main()
  document.querySelector("input[name=\"button\"]")?.addEventListener "click", client_spawner
