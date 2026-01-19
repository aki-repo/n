{ pkgs, inputs, ... }:
{
# configure options
    programs.noctalia-shell = {
      enable = true;
      settings = {
        # configure noctalia here
        templates ={
          ActiveTemaplates = [
            {
              id = "niri";
              enabled = true;
            }
            {
              id = "discord";
              enabled = true;
            }
            {
              id = "fuzzel";
              enabled = true;
            }
          ];
        };
        dock = {
          enabled = false;
        };
        ui = {
          settingsPanelMode = "center";
          #panelBackgroundOpacity = 0.5;
        };
        controlCenter = {
          position = "center";
        };
        
        bar = {
          density = "spacious";
          position = "left";
          showCapsule = false;
          outerCorners = false;
          widgets = {
            left = [
              {
                id = "ControlCenter";
                useDistroLogo = true;
              }
              {
                id = "WiFi";
              }
              {
                id = "Bluetooth";
              }
              {
                id = "Brightness";
              }
              {
                id = "Volume";
              }
              {
                id = "SystemMonitor";
              }
              {
                id = "PowerProfile";
              }
            ];
            center = [
              {
                hideUnoccupied = false;
                id = "Workspace";
                labelMode = "none";
              }
            ];
            right = [
              {
                alwaysShowPercentage = false;
                id = "Battery";
                warningThreshold = 30;
              }
              {
                formatHorizontal = "HH:mm";
                formatVertical = "HH mm";
                id = "Clock";
                useMonospacedFont = true;
                usePrimaryColor = true;
              }
            ];
          };
        };
        colorSchemes = {
          predefinedScheme = "Neutral";
          useWallpaperColors = true;
          darkMode = true;
          matugenSchemeType = "scheme-neutral";
        };
				general = {
        };
        location = {
          monthBeforeDay = true;
          name ="Washington, US";
        };
      };
      # this may also be a string or a path to a JSON file.
    };
}

