{
  description = "aki nix";

  inputs = {
    # Nixpkgs
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.11";
    nixos-hardware.url = "github:NixOS/nixos-hardware/master";
    home-manager.url = "github:nix-community/home-manager/release-24.11";
    home-manager.inputs.nixpkgs.follows = "nixpkgs";
    stylix.url = "github:danth/stylix/release-24.11";
    hyprland.url = "github:hyprwm/Hyprland";
	# ghostty.url = "github:clo4/ghostty-hm-module";
    helix.url = "github:helix-editor/helix";
    niri = {
      url = "github:sodiboo/niri-flake";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    zen-browser = {
      url = "github:linuxmobile/zen-browser-flake";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    schizofox.url = "github:schizofox/schizofox";
    
  };

  outputs = {
    self,
    nixpkgs,
    home-manager,
    nixos-hardware,
    stylix,
    helix,
    ghostty,
    schizofox,
    zen-browser,
    niri,
    hyprland,
    ...
  } @ inputs: let
    inherit (self) outputs;
  in {
    # NixOS configuration entrypoint
    # Available through 'nixos-rebuild --flake .#your-hostname'
    nixosConfigurations = {
      tp = nixpkgs.lib.nixosSystem {
        specialArgs = {inherit inputs outputs;};
        # > Our main nixos configuration file <
        modules = [ ./nixos/configuration.nix
                    nixos-hardware.nixosModules.lenovo-thinkpad-p1
                    stylix.nixosModules.stylix
                    #ghostty.homeModules.default
                  ];
      };
    };

    # Standalone home-manager configuration entrypoint
    # Available through 'home-manager --flake .#your-username@your-hostname'
    homeConfigurations = {
      "aki@tp" = home-manager.lib.homeManagerConfiguration {
        pkgs = nixpkgs.legacyPackages.x86_64-linux; # Home-manager requires 'pkgs' instance
        
          extraSpecialArgs = {inherit inputs outputs;};
        # > Our main home-manager configuration file <
        modules = [./home-manager/home.nix];
      };
    };
  };
}
