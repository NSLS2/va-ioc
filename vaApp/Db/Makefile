TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
# Create and install (or just install) into <top>.template
# databases, templates, substitutions like this

# General controller
DB += mks937b_controller.db
DB += mks937b_ccg.db
DB += mks937b_pirg.db
DB += mks937b_relay_ccg.db
DB += mks937b_relay_pirg.db

DB += gammampcq_controller.template
DB += gammampcq_ip.template
DB += gammampcq_setpoint.template
DB += gammampcq_di.template

DB += gammaspc_controller.template
DB += gammaspc_ip.template
DB += gammaspc_setpoint.template

DB_INSTALLS += $(EPICS_BASE)/db/iocAdminSoft.db
DB_INSTALLS += $(EPICS_BASE)/db/save_restoreStatus.db
DB_INSTALLS += $(EPICS_BASE)/db/reccaster.db

#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

