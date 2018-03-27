# Google breakpad client library for Swift-Android
You can read more about google brekpad [here](https://github.com/google/breakpad/blob/master/docs/getting_started_with_breakpad.md).


This is only **client** library, but you need also create a symbols for you `.so` libs, for future creating  a human-readable C/C++ stack trace. You can read more [here](https://github.com/google/breakpad/blob/master/README.ANDROID). For creating symbols you need to use `dump_syms`. Also you can use [this repo](https://github.com/readdle/google_breakpad_server) which helps you to create a symbols if you not running an LINUX.

### Installation

Navigate into **build** folder and run `build.sh` script.
*Note: depot_tool need to be installed on you [machine](https://chromium.googlesource.com/chromium/src/+/lkcr/docs/mac_build_instructions.md)*.

### Usage
You need to have configured Android-Swift project, and [Swift Package Manager](https://swift.org/package-manager/). You can clone [this](https://github.com/andriydruk/swift-java-codegen-sample) configure sample app.

##### 1. Import module into `Package.swift`
Import into your `Package.swift` file this module.
```
...
let package = Package(
    name: packageName,
    products: addGenerated([
    ]),
    dependencies: [
        .package(url: "https://github.com/andriydruk/java_swift.git", .branch("master")),
        .package(url: "https://github.com/andriydruk/swift-java.git", .branch("master")),
        .package(url: "https://github.com/andriydruk/swift-java-coder.git", .branch("master")),
        .package(url: "https://github.com/andriydruk/swift-anycodable.git", .branch("master")),
        .package(url: "https://github.com/albertaleksieiev/swift-android-google-breakpad", .branch("master")) ## ADD THIS MODULE
    ],
    targets: addGenerated([
        .target(name: packageName, dependencies: ["AnyCodable"])
    ]),
    swiftLanguageVersions: [4]
)
...
```


##### 2. Run `setUpBreakpad` from swift at startup of your Android app

```
import Breakpad
import Foundation

....

public class Initializer{
    // Pass a dump directory where your .dmp files will be stored, you can store it inside android cache directory.
    // For example run `getApplicationContext().getCacheDir()` on java and pass result in this function
    public func setupSwift(dumpDirectory: String){
        setUpBreakpad(dumpDirectory)
    }
}
....
```


##### 3. Send a .dmp file to hockeyapp(optional)
You can find `NativeCrashManager.java` inside java directory, which looking for crashes inside the dump folder, and send it into hockeyapp backend. 
<br/>
So you need to run `NativeCrashManager.handleDumpFiles(this, hockeyapp_identifier);` at begin of your `onCreate` method.
<br/>



Usecase will look like: `App runing` -> `App crashed` -> `App save .dmp files inside dump folder` -> `App closed` -> `User open app again` -> `NativeCrashManager send dumps into hockeyapp server` -> `App running` -> `...`



