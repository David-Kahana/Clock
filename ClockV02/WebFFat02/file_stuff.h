#include <FS.h>
#include <FFat.h>

// Make size of files human readable
// source: https://github.com/CelliesProjects/minimalUploadAuthESP32
String humanReadableSize(const size_t bytes) {
  if (bytes < 1024) return String(bytes) + " B";
  else if (bytes < (1024 * 1024)) return String(bytes / 1024.0) + " KB";
  else if (bytes < (1024 * 1024 * 1024)) return String(bytes / 1024.0 / 1024.0) + " MB";
  else return String(bytes / 1024.0 / 1024.0 / 1024.0) + " GB";
}

// list all of the files, if ishtml=true, return html rather than simple text
String listFiles(bool ishtml) {
  String returnText = "";
  Serial.println("Listing files stored on FFAT");
  File root = FFat.open("/");
  File foundfile = root.openNextFile();
  if (ishtml) {
    returnText += "<table><tr><th align='left'>Name</th><th align='left'>Size</th><th></th><th></th></tr>";
  }
  while (foundfile) {
    if (ishtml) {
      returnText += "<tr align='left'><td>" + String(foundfile.name()) + "</td><td>" + humanReadableSize(foundfile.size()) + "</td>";
      returnText += "<td><button onclick=\"downloadDeleteButton(\'" + String(foundfile.name()) + "\', \'download\')\">Download</button>";
      returnText += "<td><button onclick=\"downloadDeleteButton(\'" + String(foundfile.name()) + "\', \'delete\')\">Delete</button></tr>";
    } else {
      returnText += "File: " + String(foundfile.name()) + " Size: " + humanReadableSize(foundfile.size()) + "\n";
    }
    foundfile = root.openNextFile();
  }
  if (ishtml) {
    returnText += "</table>";
  }
  root.close();
  foundfile.close();
  return returnText;
}

bool mount_ffat() {
  Serial.println("Mounting FFat ...");
  if (!FFat.begin(true)) {
    // if you have not used FFAT before on a ESP32, it will show this error.
    // after a reboot FFAT will be configured and will happily work.
    Serial.println("ERROR: Cannot mount FFat, Rebooting");
    return false;
    //rebootESP("ERROR: Cannot mount FFat, Rebooting");
  }
  Serial.print("FFat Free: "); Serial.println(humanReadableSize((FFat.totalBytes() - FFat.usedBytes())));
  Serial.print("FFat Used: "); Serial.println(humanReadableSize(FFat.usedBytes()));
  Serial.print("FFat Total: "); Serial.println(humanReadableSize(FFat.totalBytes()));
  Serial.println(listFiles(false));
  return true;
}