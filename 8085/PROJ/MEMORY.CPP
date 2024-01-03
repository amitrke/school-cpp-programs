// memory realated functions
void write_to_memory(int addr, int val)
{
  mem[addr].addr = addr;
  mem[addr].content = val;
}

int read_from_memory(int addr)
{
  int count = 0;
  while((count <= MAX_MEM)&&(addr != mem[count].addr))
    {
      count++;
    };
  if (addr == mem[count].addr) return mem[count].content;
  return 0;
}

void pushme(int datatopush)
{
  datatopush = datatopush;
}
