{ pkgs, inputs, ... }:
{
# configure options
    programs.noctalia-shell = {
      enable = true;
      settings = {
        # configure noctalia here
        templates = {
				  activeTemplates = [ "gtk" "qt" "hyprland" "alacritty" "vscode" "helix" ]; 
				};
        dock = {
          enabled = false;
        };
        bar = {
          density = "comfortable";
          position = "left";
          showCapsule = false;
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
        colorSchemes.predefinedScheme = "Neutral";
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

