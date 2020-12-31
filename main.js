const { databaseHelper } = require('./resources/js/database/database-helper.js');
const fs = require('fs');
const { app } = require('electron');
const path = require('path');

let windowProvider = null;
let menu = null;
let dbname = "db.sqlite";

let dbHelper = new databaseHelper(path.join(__dirname, dbname));

const gotLock = app.requestSingleInstanceLock();

if (!gotLock) {
  app.exit(0)
  return;
}

app.on('second-instance', () => {
  windowProvider.getWindow().show()
})

/*non-MacOS*/
app.on('ready', createWindow)
/*macOS*/
app.on('activate', createWindow)

app.on('window-all-closed', () => {

})

app.on('before-quit', () => {
  app.exit(0)
})

app.userAgentFallback = app.userAgentFallback = 'Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/12.10136'

function createWindow() {
  // dbHelper.insertEvent("2020/12/31",false)
  // dbHelper.selectEvent(1).then((events) => {
  //   console.log(events)
  // })
  initialize()
  if (windowProvider.getWindow() == null) {
    windowProvider.createMainWindow()
    menu.buildMenu(windowProvider)

  } else {
    if (process.platform === 'darwin') {
      app.dock.show()
    }

    windowProvider.getWindow().show()
    menu.buildMenu(windowProvider)
  }
}

function initialize() {
  if (menu == null) {
    menu = require('./resources/js/UI/menu.js')
  }

  if (windowProvider == null) {
    windowProvider = require('./resources/js/UI/window-provider.js')
  }
}
