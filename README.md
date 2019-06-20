# Product Name
> ShoreBase  
> Version 0.1

The shore-based software is based on qt and javascript and is mainly used for monitoring and controlling underwater robots. For detailed functions, please refer to the development documentation.

![](header.png)

## File tree list
.  
├── configuredlg.cpp  
├── configuredlg.h  
├── customplotdlg.cpp  
├── customplotdlg.h  
├── debugdlg.cpp  
├── debugdlg.h  
├── emergencyparadlg.cpp  
├── emergencyparadlg.h  
├── emergencyshow.cpp  
├── emergencyshow.h  
├── main.cpp  
├── mainwindow.cpp  
├── mainwindow.h  
├── mainwindow.ui  
├── mapdialog.cpp  
├── mapdialog.h  
├── MBUtils.cpp  
├── MBUtils.h  
├── missionparadlg.cpp  
├── missionparadlg.h  
├── pathplanningdlg.cpp  
├── pathplanningdlg.h  
├── qcustomplot.cpp  
├── qcustomplot.h  
├── shoreBase.pro  
├── startandviewdlg.cpp  
├── startandviewdlg.h  
└── google Map  
    └── GoogleMapAPIv3_offlinePack        
&#160; &#160; &#160; &#160;├── images     
&#160; &#160; &#160; &#160;├── img    
&#160; &#160; &#160; &#160;├── index.html    
&#160; &#160; &#160; &#160;├── mapfiles    
&#160; &#160; &#160; &#160;└── maptile    

## Installation

Linux:  

Download the corresponding source code under Linux  
Download offline Google Map  
Place the offline Google Maps folder in the correct location  
Download QT Creator and require QT version more than 5.10  
Compile with gcc  

Windows:  

Download the corresponding source code under windows  
Download offline Google Map    
Place the offline Google Maps folder in the correct location    
Download QT Creator and require QT version more than 5.10    
Compile with MSVC  

## Usage example



_For more examples and usage, please refer to the 

## Development setup

Describe how to install all development dependencies and how to run an automated test-suite of some kind. Potentially do this for multiple platforms.

```sh
make install
npm test
```

## Release History

* 0.2.1
    * CHANGE: Update docs (module code remains unchanged)
* 0.2.0
    * CHANGE: Remove `setDefaultXYZ()`
    * ADD: Add `init()`
* 0.1.1
    * FIX: Crash when calling `baz()` (Thanks @GenerousContributorName!)
* 0.1.0
    * The first proper release
    * CHANGE: Rename `foo()` to `bar()`
* 0.0.1
    * Work in progress

## Meta

Your Name – [@YourTwitter](https://twitter.com/dbader_org) – YourEmail@example.com

Distributed under the XYZ license. See ``LICENSE`` for more information.

[https://github.com/yourname/github-link](https://github.com/dbader/)

## Contributing

1. Fork it (<https://github.com/yourname/yourproject/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request
