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
          pname = "swww-frontend";
          version = "0.1";

          src = ./.;

          buildInputs = with pkgs; [ gtk3 pkg-config ];

          installPhase = ''
            mkdir -p $out/bin
            gcc main.c -o $out/bin/swww-frontend `pkg-config --cflags --libs gtk+-3.0`
          '';
        };
      in {
        packages.default = gtkApp;
        apps.default = flake-utils.lib.mkApp {
          drv = gtkApp;
        };
      });
}
