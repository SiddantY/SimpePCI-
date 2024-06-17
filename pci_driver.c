#define VENDOR_ID 0x1000
#define DEVICE_ID 0x0000

int init_module(void)
{
  return pci_module_init(&pci_driver_DevicePCI);
}

void cleanup_module(void)
{
  pci_unregister_driver(&pci_driver_DevicePCI);
}

int device_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
  int ret;
  ret = pci_enable_device(dev);
  if (ret < 0) return ret;

  ret = pci_request_regions(dev, "MyPCIDevice");
  if (ret < 0) 
  {
    pci_disable_device(dev);
    return ret;
  }

  return 0;
}

void device_remove(struct pci_dev *dev)
{
  pci_release_regions(dev);
  pci_disable_device(dev);
}

struct pci_device_id  pci_device_id_DevicePCI[] = 
{
  {VENDOR_ID, DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
  {}  // end of list
};

struct pci_driver  pci_driver_DevicePCI = 
{
  name: "MyPCIDevice",
  id_table: pci_device_id_DevicePCI,
  probe: device_probe,
  remove: device_remove
};
