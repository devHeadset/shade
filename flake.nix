{
  description = "GTK frontend for swww";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        gtkApp = pkgs.stdenv.mkDerivation {
        pname = "shade";
        version = "0.1";

  src = ./.;

  buildInputs = [ pkgs.stdenv.cc pkgs.gtk3 pkgs.pkg-config ];

  buildPhase = ''
    gcc main.c ui.c swww.c -o shade $(pkg-config --cflags --libs gtk+-3.0)
  '';

  installPhase = ''
      mkdir -p $out/bin
     cp shade $out/bin/
     '';
 };
     in {
        packages.default = gtkApp;
        apps.default = flake-utils.lib.mkApp {
          drv = gtkApp;
        };
      });
}
