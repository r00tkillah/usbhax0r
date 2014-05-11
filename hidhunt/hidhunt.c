#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/kprobes.h>
#include<linux/kallsyms.h>

#include <linux/hardirq.h>
#include <linux/debugfs.h>

static struct jprobe hid_register_report_probe;

static asmlinkage int hijack_hid_register_report(struct hid_device *device, unsigned type, unsigned id)
{
  printk("HIDHUNTER :: hid_register_report called\n");
  jprobe_return();
  return 0;
}

int init_module(void)
{
  // hook debugfs
  hid_register_report_probe.entry=(kprobe_opcode_t*)hijack_hid_register_report;
  hid_register_report_probe.kp.addr=(kprobe_opcode_t*)kallsyms_lookup_name("hid_register_report");
  register_jprobe(&hid_register_report_probe);
  printk("HIDHUNTER :: hid_register_report hooked\n");

  return 0;
}

void cleanup_module(void)
{
  unregister_jprobe(&hid_register_report_probe);
  printk("ASPROBE :: jprobes unregistered\n");
}

MODULE_LICENSE("GPL");
