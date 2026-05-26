add_files -norecurse -fileset constrs_1 [subst {$ROOT_FOLDER/designs/$project_name/syn/constraints/ovc_spi_CBX1X.xdc}]
set_property generic {BOARD_REV="CBX1X"} [current_fileset]
