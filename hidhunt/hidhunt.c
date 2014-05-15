
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/kprobes.h>
#include<linux/kallsyms.h>

#include <linux/hardirq.h>
#include <linux/debugfs.h>

static struct jprobe hid_register_report_probe;
static struct jprobe hid_add_field_probe;
static struct jprobe hid_parser_main_probe;
static struct jprobe hid_parser_global_probe;
static struct jprobe hid_parser_local_probe;
static struct jprobe hid_parser_reserved_probe;

static asmlinkage int hijack_hid_register_report(void)
{
  printk("HIDHUNTER :: hid_register_report() called\n");
  jprobe_return();
  return 0;
}

static asmlinkage int hijack_hid_add_field(void)
{
  printk("HIDHUNTER :: hid_add_field() called\n");
  jprobe_return();
  return 0;
}

static asmlinkage int hijack_hid_parser_main(void)
{
  printk("HIDHUNTER :: hid_parser_main() called\n");
  jprobe_return();
  return 0;
}

static asmlinkage int hijack_hid_parser_global(void)
{
  printk("HIDHUNTER :: hid_parser_global() called\n");
  jprobe_return();
  return 0;
}

static asmlinkage int hijack_hid_parser_local(void)
{
  printk("HIDHUNTER :: hid_parser_local() called\n");
  jprobe_return();
  return 0;
}

static asmlinkage int hijack_hid_parser_reserved(void)
{
  printk("HIDHUNTER :: hid_parser_reserved() called\n");
  jprobe_return();
  return 0;
}

int init_module(void)
{
  hid_register_report_probe.entry=(kprobe_opcode_t*)hijack_hid_register_report;
  hid_register_report_probe.kp.addr=(kprobe_opcode_t*)kallsyms_lookup_name("hid_register_report");
  register_jprobe(&hid_register_report_probe);
  printk("HIDHUNTER :: hid_register_report hooked\n");

  hid_add_field_probe.entry=(kprobe_opcode_t*)hijack_hid_add_field;
  hid_add_field_probe.kp.addr=(kprobe_opcode_t*)kallsyms_lookup_name("hid_add_field");
  register_jprobe(&hid_add_field_probe);
  printk("HIDHUNTER :: hid_add_field hooked\n");

  hid_parser_main_probe.entry=(kprobe_opcode_t*)hijack_hid_parser_main;
  hid_parser_main_probe.kp.addr=(kprobe_opcode_t*)kallsyms_lookup_name("hid_parser_main");
  register_jprobe(&hid_parser_main_probe);
  printk("HIDHUNTER :: hid_parser_main hooked\n");

  hid_parser_global_probe.entry=(kprobe_opcode_t*)hijack_hid_parser_global;
  hid_parser_global_probe.kp.addr=(kprobe_opcode_t*)kallsyms_lookup_name("hid_parser_global");
  register_jprobe(&hid_parser_global_probe);
  printk("HIDHUNTER :: hid_parser_global hooked\n");

  hid_parser_local_probe.entry=(kprobe_opcode_t*)hijack_hid_parser_local;
  hid_parser_local_probe.kp.addr=(kprobe_opcode_t*)kallsyms_lookup_name("hid_parser_local");
  register_jprobe(&hid_parser_local_probe);
  printk("HIDHUNTER :: hid_parser_local hooked\n");

  hid_parser_reserved_probe.entry=(kprobe_opcode_t*)hijack_hid_parser_reserved;
  hid_parser_reserved_probe.kp.addr=(kprobe_opcode_t*)kallsyms_lookup_name("hid_parser_reserved");
  register_jprobe(&hid_parser_reserved_probe);
  printk("HIDHUNTER :: hid_parser_reserved hooked\n");

  return 0;
}

void cleanup_module(void)
{
  unregister_jprobe(&hid_register_report_probe);
  unregister_jprobe(&hid_add_field_probe);
  unregister_jprobe(&hid_parser_main_probe);
  unregister_jprobe(&hid_parser_global_probe);
  unregister_jprobe(&hid_parser_local_probe);
  unregister_jprobe(&hid_parser_reserved_probe);
  printk("HIDHUNTER :: jprobes unregisterd\n");
}

MODULE_LICENSE("GPL");
