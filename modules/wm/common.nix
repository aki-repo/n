# hyprland configuration

{inputs, pkgs, ...}: {


  home.packages = with pkgs; [
    dunst
    nemo
    vscode
    librewolf
    chromium
    microfetch
    nwg-look
    qutebrowser
    google-chrome
    easyeffects
    mpd
    rmpc
    ];


}
