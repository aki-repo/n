{ pkgs, lib, ... }:
{
    stylix = {
    enable = true;
    polarity = "dark";

    image = ./modules/w/schweiz.jpg;
    iconTheme = {
			enable = true;
	 		package = pkgs.papirus-icon-theme;
	 		light = "Papirus";
	 		dark = "Paprius Dark";
	 	};
    cursor = {
 	       		package = pkgs.bibata-cursors;
 	       		name = "Bibata-Modern-Classic";
 	       		size = 24;
 	       	};
 	       	fonts = {
 	       		sizes = {
 	       			terminal = 14;
 	       			desktop = 12;
 	       		};

 	       		monospace = {
 	       			package = pkgs.nerd-fonts.jetbrains-mono;
 	       			name = "JetBrainsMono Nerd Font Mono";
 	       		};
 	       		sansSerif = {
 	       			package = pkgs.dejavu_fonts;
 	       			name = "DejaVu Sans";
 	       		};
 	       		serif = {
 	       			package = pkgs.dejavu_fonts;
 	       			name = "DejaVu Serif";
 	       		};
 	       	};
  };

}