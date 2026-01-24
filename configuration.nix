{ inputs, config, pkgs, lib, ... }:

{
  imports =
    [ # Include the results of the hardware scan.
      ./hardware-configuration.nix
      #./modules/gnome.nix
      ./modules/stylix.nix
    ];

  # Bootloader.
  boot.loader.systemd-boot.enable = true;
  boot.loader.efi.canTouchEfiVariables = true;

  #bluetooth
  hardware.bluetooth.enable = true;

  # swap
  zramSwap.enable = true;

  # power
  services.thermald.enable = true;

  services.tuned.enable = true;
  services.upower.enable = true;

  networking.hostName = "nixos-btw"; # Define your hostname.

  # Enable networking
  networking.networkmanager.enable = true;

  # Set your time zone.
  time.timeZone = "America/New_York";

  # Select internationalisation properties.
  i18n.defaultLocale = "en_US.UTF-8";

  i18n.extraLocaleSettings = {
    LC_ADDRESS = "en_US.UTF-8";
    LC_IDENTIFICATION = "en_US.UTF-8";
    LC_MEASUREMENT = "en_US.UTF-8";
    LC_MONETARY = "en_US.UTF-8";
    LC_NAME = "en_US.UTF-8";
    LC_NUMERIC = "en_US.UTF-8";
    LC_PAPER = "en_US.UTF-8";
    LC_TELEPHONE = "en_US.UTF-8";
    LC_TIME = "en_US.UTF-8";
  };

  hardware = {
    graphics.enable = true;
    nvidia = {
      modesetting.enable = true;
      open = true;
    };
    nvidia.prime = {
       intelBusId = "PCI:0:2:0";
       nvidiaBusId = "PCI:1:0:0";
    };
  };

  security.polkit.enable = true;

  # Enable the X11 windowing system.
  services.xserver = {
    videoDrivers = [ "nvidia" ];
    enable = true;
    autoRepeatDelay = 200;
    autoRepeatInterval = 35;
    displayManager.lightdm.greeters.gtk.enable =true;
		#windowManager.qtile.enable = true;
    };    

  environment.sessionVariables.NIXOS_OZONE_WL = "1";

  programs.hyprland = {
    enable = true;
    withUWSM = true;
		xwayland.enable = true;
		# set the flake package
    package = inputs.hyprland.packages.${pkgs.stdenv.hostPlatform.system}.hyprland;
    # make sure to also set the portal package, so that they are in sync
    portalPackage = inputs.hyprland.packages.${pkgs.stdenv.hostPlatform.system}.xdg-desktop-portal-hyprland;
  };


  programs.niri.enable = true;

  #services.xserver.displayManager.lightdm = {
  #  enable = true;

    # Setting gtk as the greeter
  #  greeters.gtk.enable = true;

    # Example of having background as a particular color
    #background = "#ffa07a";

    # Example of the default image background (must be an absolute path)
    #background = pkgs.nixos-artwork.wallpapers.simple-dark-gray-bottom.gnomeFilePath;

  #};

  # Configure keymap in X11
  services.xserver.xkb = {
    layout = "us";
    variant = "";
  };

  # Enable CUPS to print documents.
  services.printing.enable = true;

  # Enable sound with pipewire.
  services.pulseaudio.enable = false;
  security.rtkit.enable = true;
  services.pipewire = {
    enable = true;
    alsa.enable = true;
    alsa.support32Bit = true;
    pulse.enable = true;
    # If you want to use JACK applications, uncomment this
    #jack.enable = true;

  };

  # Enable touchpad support (enabled default in most desktopManager).
  # services.xserver.libinput.enable = true;

  # Define a user account. Don't forget to set a password with ‘passwd’.
  users.users.aki = {
    isNormalUser = true;
    description = "aki";
    extraGroups = [ "networkmanager" "wheel" ];
    packages = with pkgs; [
    #  thunderbird
    ];
  };

  # Install firefox.
  # programs.firefox.enable = true;

  # Allow unfree packages
  nixpkgs.config.allowUnfree = true;

  # List packages installed in system profile. To search, run:
  # $ nix search wget
  environment.systemPackages = with pkgs; [
    alacritty
    kitty
  ];
  
  programs.nh = {
    enable = true;
		clean.enable = true;
		clean.extraArgs = "--keep-since 5d --keep 3";
		flake = "/home/aki/c/n";
	};
  
	nix.settings = {
    substituters = ["https://hyprland.cachix.org"];
    trusted-substituters = ["https://hyprland.cachix.org"];
    trusted-public-keys = ["hyprland.cachix.org-1:a7pgxzMz7+chwVL3/pzj6jIBMioiJM7ypFP8PwtkuGc="];
    experimental-features = [ "nix-command" "flakes" ];
   };

  system.stateVersion = "25.11";

}
