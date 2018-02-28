D8 Audit
======

This Drush plugin provides a Drush command to quickly run a module audit for a D8 migration. Currently, the script will fetch a list of all enabled plugins, run them against the 8.x project API, and check if an 8.x version of the module is available.

Here is an example output.

```
----------------------------------------------------------------------------------------------------
 ✓  nodeaccess                                 Access control               8.x-1.0-beta1   beta1  
    roles_for_menu                             Access control                                      
 ✓  admin_menu                                 Administration               8.x-3.x-dev     dev    
    adminimal_admin_menu                       Administration                                      
    admin_menu_source                          Administration                                      
    admin_views                                Administration                                      
 ✓  fpa                                        Administration               8.x-2.x-dev     dev    
 ✓  filter_perms                               Administration               8.x-1.x-dev     dev    
 ✓  module_filter                              Administration               8.x-3.1                
 ✓  ctools                                     Chaos tool suite             8.x-3.0                
    scrambler                                  Data security                                       
    scrambler_ui                               Data security                                       
    scrambler_user                             Data security                                       
 ✓  date                                       Date/Time                    8.x-1.x-dev     dev    
    date_api                                   Date/Time                                           
 ✓  date_popup                                 Date/Time                    8.x-1.0                
    date_views                                 Date/Time                                           
    dbinfo                                     Development                                         
 ✓  devel                                      Development                  8.x-1.2                
 ✓  elasticsearch_connector                    Elasticsearch                8.x-5.0-alpha2  alpha2 
 ✓  webform                                    Webform                      8.x-5.0-rc3     rc3    
 ✓  workbench                                  Workbench                    8.x-1.0                
 ✓  workbench_email                            Workbench                    8.x-1.0-alpha7  alpha7 
 ✓  workbench_moderation                       Workbench                    8.x-1.3
 ----------------------------------------------------------------------------------------------------
TOTAL COUNT
 Ready Status  Count 
 Yes           14    
 No            10   
 Total         24
 ```
