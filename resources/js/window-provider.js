(function() {
  const { BrowserWindow, BrowserView, app } = require('electron')

  const windowStateKeeper = require('electron-window-state')
  const configurator = require('./browserview-configurator.js')
  const path = require('path')
  const url = require('url')

  let mainWindow = null
  let browserView = null

  var createMainWindow = () => {
    let windowState = windowStateKeeper( { defaultWidth: 1400, defaultHeight: 1000 } )
    let browser = new BrowserView({ webPreferences: { nodeIntegration: false } })
    let window = new BrowserWindow( {
      title: "Google Calendar", icon: path.join(__dirname, '../../build/icon.png'),
      x: windowState.x, y: windowState.y, width: windowState.width, height: windowState.height,
    } )
    window.setMenu(null)

    window.setBrowserView(browser)
    configurator.prepare(window, browser)

    window.on('close', (event) => {
      event.preventDefault()
      window.hide()
    })

    window.on('closed', (event) => {
      event.preventDefault()
    })

    setWindow(window)
    setBrowserView(browser)

    windowState.manage(window)

    return window
  }

  var setWindow = (w) => {
    mainWindow = w
  }

  var getWindow = () => {
    return mainWindow
  }

  var setBrowserView = (b) => {
    browserView = b
  }

  var getBrowserView = () => {
    return browserView
  }

  module.exports.createMainWindow = createMainWindow
  module.exports.getWindow = getWindow
  module.exports.getBrowserView = getBrowserView
}())
