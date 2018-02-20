roberta-ros version 1.1a
========================
ROS interface to Roberta.  (c) Gomtec GmbH.

This is an alpha release and may still contain bugs.  If you find any problems, please
get back to us.  See http://www.gomtec.de/ for further information.


To get started, proceed as follows:

1) set the path of where you installed these downloaded files, e.g.:

	ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:/home/YOURHOMEDIR/gomtec/roberta-ros/

The syntax of the above depends for your shell.  The above is for bash (or sh); for csh, zsh, etc. use something like

	setenv ROS_PACKAGE_PATH ${ROS_PACKAGE_PATH}:/home/YOURHOMEDIR/gomtec/roberta-ros/

2) go to the corresponding subdirectory:

	roscd gomtec_robot_description

3) run:

	roslaunch gomtec_robot_description display.launch model:=urdf/Roberta_P80_800.urdf gui:=true

   or:

	roslaunch gomtec_robot_description display_p80_800.launch


Good luck!  Please contact us if you run into trouble, at ros--at--gomtec dot de.
