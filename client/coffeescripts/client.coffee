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
  myPixel: {x: null, y: null, red: null, green: null, blue: null}

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

  joinServer: =>
    socket = chrome.socket
    socket.create 'udp', {}, (socketInfo) =>
      @socket_info = socketInfo
      socket.connect @socket_info.socketId, @server_address, @port, (connectResult) =>
        socket.write @socket_info.socketId, @str2ab("HELLO\n"), (writeInfo) ->
          console.debug "writeinfo", writeInfo


  # str2ab: Takes a string and turns it into an arraybuffer.
  #   ArrayBuffer takes the number of bytes to allocate.
  #   ArrayBuffers must be accessed via a DataView. In this case a Uint8Array.

  str2ab: (str) ->
    buf = new ArrayBuffer(str.length)
    bufView = new Uint8Array(buf)
    bufView[i] = str.charCodeAt(i) for i in [0...str.length]
    buf

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

  addPixel: (x, y, r, g, b) =>
    @grid[x][y].occupancy.push {red: r, green: g, blue: b}

  #Update function
  update: =>
    if @socket_info?
      chrome.socket.read @socket_info.socketId, (readInfo) =>
        console.debug "Reading..."
        if readInfo.resultCode > 0
          ab2str = (ab) ->
            String.fromCharCode.apply null, new Uint8Array(ab)
          @react ab2str(readInfo.data)
    @drawGrid()

    setTimeout @update, @updateLength

  #Catch messages from the server and react accordingly.
  react: (str) =>
    console.debug str
    #If PING, reply PONG.
    if str.match /^PING/
      console.debug "CAUGHT PING"
      return chrome.socket.write @socket_info.socketId, @str2ab("PONG\n"), (writeInfo) ->
        console.debug "writeinfo", writeInfo
    #If WELCOME, fill-in @myPixel
    m = /^WELCOME: x:(\d+),y:(\d+),r:(\d+),g:(\d+),b:(\d+)/.exec str
    if m?
      console.debug "CAUGHT WELCOME"
      m = m.map (i) -> parseInt(i, 10)
      return @myPixel = {x: m[1], y: m[2], red: m[3], green: m[4], blue: m[5]}
    #If $ ended location, update occupancy list. First remove the pixel with that rgb, then re-add it to the grid.
    m = /(\d+),(\d+),(\d+),(\d+),(\d+)\$/.exec str
    if m?
      console.debug "m:", m
      console.debug "CAUGHT pixeldata$"
      console.debug "m[1]: #{m[1]} m[2]: #{m[2]}"
      m = m.map (i) -> parseInt(i, 10)
      console.debug "m[1]: #{m[1]} m[2]: #{m[2]}"
      for row in [0...@numberOfRows]
        for column in [0...@numberOfColumns]
          #deepEquals function for equality of arrays by element.
          deepEquals = (list1, list2) ->
            if list1.length isnt list2.length then return false
            return false for i in [0...list1.length] when list1[i] isnt list2[i]
            return true

          @grid[row][column].occupancy = (p for p in @grid[row][column].occupancy when not deepEquals([p.red, p.green, p.blue], [m[3], m[4], m[5]]))
          #console.log "row: #{row} column: #{column} m[1]: #{m[1]} m[2]: #{m[2]}"
          if deepEquals([row, column], [m[1], m[2]])
            console.log "Equality 4 all!"
            @grid[row][column].occupancy.push {red: m[3], green: m[4], blue: m[5]}

  drawGrid: ->
    for row in [0...@numberOfRows]
      for column in [0...@numberOfColumns]
        @drawCell @grid[row][column]

  drawCell: (cell) ->
    x = cell.column * @cellSize
    y = cell.row * @cellSize

    if cell.occupancy.length is 0
      fillStyle = 'rgb(38, 38, 38)'
    else
      #Fill the cell with the average rgb of all pixels in its occupancy list.
      [r,g,b] = [0,0,0]
      [r,g,b] = [r+p.red, g+p.green, b+p.blue] for p in cell.occupancy
      [r,g,b] = [r/cell.occupancy.length, g/cell.occupancy.length, b/cell.occupancy.length]
      fillStyle = "rgb(#{r}, #{g}, #{b})"
      console.log fillStyle
    
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
