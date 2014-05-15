import os
from random import randint

targets = "hid_register_report","hid_add_field","hid_parser_main","hid_parser_global","hid_parser_local","hid_parser_reserved"

#try:
#  os.rename("hidhunt.c","hidhunt.c-bak"+str(randint(0,99999)))
#except:
#  print "no file to back up .. okay"

codefile = open("hidhunt.c","w")

# write includes
codefile.write('''
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/kprobes.h>
#include<linux/kallsyms.h>

#include <linux/hardirq.h>
#include <linux/debugfs.h>

''')

# write declarations
for target in targets:
  codefile.write("static struct jprobe "+target+"_probe;\n")

# write hijack stubs
for target in targets:
  codefile.write('''
static asmlinkage int hijack_'''+target+'''(void)
{
  printk("HIDHUNTER :: '''+target+'''() called\\n");
  jprobe_return();
  return 0;
}
''')

# init module
codefile.write('''
int init_module(void)
{''')

for target in targets:
  codefile.write('''
  '''+target+'''_probe.entry=(kprobe_opcode_t*)hijack_'''+target+''';
  '''+target+'''_probe.kp.addr=(kprobe_opcode_t*)kallsyms_lookup_name("'''+target+'''");
  register_jprobe(&'''+target+'''_probe);
  printk("HIDHUNTER :: '''+target+''' hooked\\n");
''')

codefile.write('''
  return 0;
}
''')

# cleanup module
codefile.write('''
void cleanup_module(void)
{''')

for target in targets:
  codefile.write('''
  unregister_jprobe(&'''+target+'''_probe);''')

codefile.write('''
  printk("HIDHUNTER :: jprobes unregisterd\\n");
}

MODULE_LICENSE("GPL");
''')
