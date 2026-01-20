{ pkgs, lib, ... }:

{
    pkgs = with pkgs; [
        tradingview
        zulu
    ];
}