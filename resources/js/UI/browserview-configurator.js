(function () {

  var prepare = (window, browser) => {
    setBounds(window, browser)
    browser.setAutoResize({ width: true, height: true })
    browser.webContents.userAgent = 'Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/12.10136'
    browser.webContents.loadURL('https://calendar.google.com/')
    browser.webContents.on("new-window", (event, url) => {
      try {
        require("electron").shell.openExternal(url);
        event.preventDefault();
      } catch (error) {
        // console.log("Ignoring " + url + " due to " + error.message);
      }
    });
  }

  var setBounds = (window, browser) => {
    browser.setBounds({
      x: 0,
      y: getTitleBarOffset(),
      width: window.getBounds().width,
      height: window.getBounds().height - getTitleBarSize(window)
    });
  }

  function getTitleBarSize(window) {
    if (process.platform === "darwin") {
      return 20;
    } else if (process.platform === "win32") {
      return window.isMenuBarVisible() ? 60 : 40;
    } else {
      return window.isMenuBarVisible() ? 25 : 0;
    }
  }

  function getTitleBarOffset() {
    if (process.platform === "darwin") {
      return 0;
    } else if (process.platform === "win32") {
      return 0;
    } else {
      return 0;
    }
  }

  module.exports.prepare = prepare
  module.exports.setBounds = setBounds
}())
