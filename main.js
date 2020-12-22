const { app } = require('electron')

let windowProvider = null
let menu = null

const gotLock = app.requestSingleInstanceLock()

if (!gotLock) {
  app.exit(0)
  return;
}

app.on('second-instance', () => {
  windowProvider.getWindow().show()
})

app.on('ready', createWindow)
app.on('activate', createWindow)

app.on('window-all-closed', () => {

})

app.on('before-quit', () => {
  app.exit(0)
})

app.userAgentFallback = app.userAgentFallback = 'Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/12.10136'

function createWindow() {
  initialize()

  if (windowProvider.getWindow() == null) {
    windowProvider.createMainWindow()
  } else {
    if (process.platform === 'darwin') {
      app.dock.show()
    }

    windowProvider.getWindow().show()
  }
}

function initialize() {
  if (windowProvider == null) {
    windowProvider = require('./resources/js/window-provider.js')
  }
}
