# MANA

##Package Manager Manager

At the current stage, Mana is still incomplete.
Crucial Features like detection of managers, finding the correct path for the managers to call, as well as error checks. I would not recommend using Mana in its current stage.

Mana is a Package Manager Manager. It lets the user do certain options across several Package managers. Those actions are:

### Update

Update the packages of all managers.

### Find <package>

Find which managers have a certain package installed, together with the version.

### Search <package>

Search across all managers for a package. All found packages are displayed with their versions and the user can decide from which manager to install.

### Delete <package>

Find all package installed with the name. All found packages are displayed together with the version. The user can then decide which package to delete.

## Supported Managers

Currently, only three Managers are supported:
APT
Homebrew
Npm
