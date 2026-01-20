{ pkgs, lib, ... }:

{
    home.packages = with pkgs; [
        tradingview
        jdk
    ];
}