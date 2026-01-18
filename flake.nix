{
  description = "NixOS aki";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";

    hyprland.url = "github:hyprwm/Hyprland";
    
		noctalia = {
      url = "github:noctalia-dev/noctalia-shell";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    stylix = {
      url = "github:nix-community/stylix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    home-manager = {
      url = "github:nix-community/home-manager/";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = { self, nixpkgs, home-manager, hyprland, stylix, noctalia,  ... } @ inputs:
  let
    inherit (self) outputs;
  in {
    nixosConfigurations.nixos-btw = nixpkgs.lib.nixosSystem {
      system = "x86_64-linux";
      specialArgs = { inherit inputs outputs; };
      modules = [
        ./configuration.nix
        stylix.nixosModules.stylix
        home-manager.nixosModules.home-manager
        {     
	      home-manager = {
	        extraSpecialArgs = { inherit inputs; };
            useGlobalPkgs = true;
            useUserPackages = true;
            users.aki = {
						  imports = [
							  ./home.nix
								inputs.noctalia.homeModules.default
								];
				     };
          };
	      }
      ];
    };
  };
}
