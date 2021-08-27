{
  "targets": [
    {
      "include_dirs" : [
        "<!(node -e \"require('nan')\")",
        "../obs-studio/lib-obs/"
        "../obs-studio/UI/"
        "../obs-studio/plugins/"
        "../MyObsLibs/headers"  #contains headers for the library I create

      ],
      "target_name": "addon",
      "library_dirs": [ "./libs" ] #contains all libobs supplied libraries and the custom library MylibObs.so (which I m not able to build yet)
      "sources": [ "example.cc" ]
    }
  ]
}
