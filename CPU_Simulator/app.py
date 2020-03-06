#!/usr/bin/python

program_counter = 0

def write_to_file_new_value(all_registers, binary_instruction, registerFile, reg2):

    count = 0
    for line in all_registers:
        if count != int(binary_instruction[4:8], 2): # if it is not register to write
            registerFile.write(line)  # we only change one registers values, so another lines is not gonna change
        else:
            registerFile.write('{0:018b}'.format(reg2))  # only this line changes
            registerFile.write('\n')
        count = count + 1
    return


def print_registers(reg0, reg1, reg2):

    print(reg0)
    print(reg1)
    print(reg2)
    return

def print_registers_with_imm_val(reg0, reg2, imm):

    print(reg0)
    print(reg2)
    print(imm)
    return

def add_instruction(binary_instruction):

    print("ADD R%d R%d R%d" %(int(binary_instruction[4:8], 2), int(binary_instruction[8:12], 2), int(binary_instruction[12:16], 2))) # prints the instruction, nothing more

    registerFile = open("register_memory.txt", "r") # open register file to hold values of registers in array
    all_registers = registerFile.readlines() # registers

    reg0 = all_registers[int(binary_instruction[8:12], 2)] # reg0 does not mean it is r0, it indicates it is one of the register to sum up values
    reg1 = all_registers[int(binary_instruction[12:16], 2)] # same
    reg2 = int(reg0, 2) + int(reg1, 2) # sum of two registers values

    registerFile.close()

    registerFile = open("register_memory.txt", "w") # now we re arrange values of registers

    write_to_file_new_value(all_registers, binary_instruction, registerFile, reg2)
    #print_registers(reg0, reg1, reg2)

    global program_counter
    program_counter += 1
    return

def and_instruction(binary_instruction):

    print("AND R%d R%d R%d" %(int(binary_instruction[4:8], 2), int(binary_instruction[8:12], 2), int(binary_instruction[12:16], 2))) # prints the instruction, nothing more

    registerFile = open("register_memory.txt", "r")
    all_registers = registerFile.readlines()

    reg0 = all_registers[int(binary_instruction[8:12], 2)]
    reg1 = all_registers[int(binary_instruction[12:16], 2)]
    reg2 = int(reg0, 2) & int(reg1, 2)

    registerFile.close()

    registerFile = open("register_memory.txt", "w")

    write_to_file_new_value(all_registers, binary_instruction, registerFile, reg2)
    #print_registers(reg0, reg1, reg2)

    global program_counter
    program_counter += 1
    return

def or_instruction(binary_instruction):

    print("OR R%d R%d R%d" % (int(binary_instruction[4:8], 2), int(binary_instruction[8:12], 2), int(binary_instruction[12:16], 2)))  # prints the instruction, nothing more

    registerFile = open("register_memory.txt", "r")
    all_registers = registerFile.readlines()

    reg0 = all_registers[int(binary_instruction[8:12], 2)]
    reg1 = all_registers[int(binary_instruction[12:16], 2)]
    reg2 = int(reg0, 2) | int(reg1, 2)

    registerFile.close()

    registerFile = open("register_memory.txt", "w")

    write_to_file_new_value(all_registers, binary_instruction, registerFile, reg2)
    #print_registers(reg0, reg1, reg2)

    global program_counter
    program_counter += 1
    return

def xor_instruction(binary_instruction):

    print("XOR R%d R%d R%d" % (int(binary_instruction[4:8], 2), int(binary_instruction[8:12], 2), int(binary_instruction[12:16], 2)))  # prints the instruction, nothing more
    registerFile = open("register_memory.txt", "r")

    all_registers = registerFile.readlines()

    reg0 = all_registers[int(binary_instruction[8:12], 2)]
    reg1 = all_registers[int(binary_instruction[12:16], 2)]
    reg2 = int(reg0, 2) ^ int(reg1, 2)

    registerFile.close()

    registerFile = open("register_memory.txt", "w")

    write_to_file_new_value(all_registers, binary_instruction, registerFile, reg2)
    #print_registers(reg0, reg1, reg2)

    global program_counter
    program_counter += 1
    return

def addi_instruction(binary_instruction):

    print("ADDI R%d R%d %d" % (int(binary_instruction[4:8], 2), int(binary_instruction[8:12], 2), int(binary_instruction[12:18], 2)))  # prints the instruction, nothing more

    registerFile = open("register_memory.txt", "r")
    all_registers = registerFile.readlines()

    reg0 = all_registers[int(binary_instruction[8:12], 2)]
    imm = int(binary_instruction[12:18], 2)
    reg2 = int(reg0, 2) + imm

    registerFile.close()

    registerFile = open("register_memory.txt", "w")

    write_to_file_new_value(all_registers, binary_instruction, registerFile, reg2)
    #print_registers_with_imm_val(reg0, reg2, imm)

    global program_counter
    program_counter += 1
    return

def andi_instruction(binary_instruction):

    print("ANDI R%d R%d %d" % (int(binary_instruction[4:8], 2), int(binary_instruction[8:12], 2), int(binary_instruction[12:18], 2)))  # prints the instruction, nothing more

    registerFile = open("register_memory.txt", "r")
    all_registers = registerFile.readlines()

    reg0 = all_registers[int(binary_instruction[8:12], 2)]
    imm = int(binary_instruction[12:18], 2)
    reg2 = int(reg0, 2) & imm

    registerFile.close()

    registerFile = open("register_memory.txt", "w")

    write_to_file_new_value(all_registers, binary_instruction, registerFile, reg2)
    #print_registers_with_imm_val(reg0, reg2, imm)

    global program_counter
    program_counter += 1
    return

def ori_instruction(binary_instruction):

    print("ORI R%d R%d %d" % (int(binary_instruction[4:8], 2), int(binary_instruction[8:12], 2), int(binary_instruction[12:18], 2)))  # prints the instruction, nothing more

    registerFile = open("register_memory.txt", "r")
    all_registers = registerFile.readlines()

    reg0 = all_registers[int(binary_instruction[8:12], 2)]
    imm = int(binary_instruction[12:18], 2)
    reg2 = int(reg0, 2) | imm

    registerFile.close()

    registerFile = open("register_memory.txt", "w")

    write_to_file_new_value(all_registers, binary_instruction, registerFile, reg2)
    #print_registers_with_imm_val(reg0, reg2, imm)

    global program_counter
    program_counter += 1
    return

def xori_instruction(binary_instruction):

    print("XORI R%d R%d %d" % (int(binary_instruction[4:8], 2), int(binary_instruction[8:12], 2), int(binary_instruction[12:18], 2)))  # prints the instruction, nothing more

    registerFile = open("register_memory.txt", "r")
    all_registers = registerFile.readlines()

    reg0 = all_registers[int(binary_instruction[8:12], 2)]
    imm = int(binary_instruction[12:18], 2)

    reg2 = int(reg0, 2) ^ imm

    registerFile.close()

    registerFile = open("register_memory.txt", "w")

    write_to_file_new_value(all_registers, binary_instruction, registerFile, reg2)
    #print_registers_with_imm_val(reg0, reg2, imm)

    global program_counter
    program_counter += 1
    return

def jump_instruction(binary_instruction):

    global program_counter

    print("JMP %d" % (int(binary_instruction[4:18], 2)))  # prints the instruction, nothing more
    program_counter += int(binary_instruction[4:18], 2)


    return

def load_instruction(binary_instruction): # loads to register from memory

    print("LD R%d Mem[%d]" % (int(binary_instruction[4:8], 2), int(binary_instruction[8:18], 2)))  # prints the instruction, nothing more

    registerFile = open("register_memory.txt", "r")
    all_registers = registerFile.readlines()

    address_line_in_decimal = int(binary_instruction[8:18], 2)
    registerFile.close()

    memoryFile = open("memory.txt", "r")
    all_addresses = memoryFile.readlines()

    count = 0
    dataToLoad = 0
    for address in all_addresses:

        if(address_line_in_decimal == count):
            dataToLoad = int(address[0:18], 2)
            #print(dataToLoad)
            break

        count = count + 1

    registerFile = open("register_memory.txt", "w")
    write_to_file_new_value(all_registers, binary_instruction, registerFile, dataToLoad)

    global program_counter
    program_counter += 1
    return

def store_instruction(binary_instruction):

    print("ST R%d Mem[%d]" % (int(binary_instruction[4:8], 2), int(binary_instruction[8:18], 2)))  # prints the instruction, nothing more

    registerFile = open("register_memory.txt", "r")
    all_registers = registerFile.readlines()
    registerFile.close()
    dataToStore = int(all_registers[int(binary_instruction[4:8], 2)], 2)

    address_line_in_decimal = int(binary_instruction[8:18], 2)

    memoryFile = open("memory.txt", "r")
    all_addresses = memoryFile.readlines()
    memoryFile.close()

    #print("Data to store:", dataToStore)

    memoryFile = open("memory.txt", "w")
    count = 0
    for address in all_addresses:
        if address_line_in_decimal != count:  # if it is not register to write
            memoryFile.write(address)  # we only change one registers values, so another lines is not gonna change
        else:
            memoryFile.write('{0:018b}\n'.format(dataToStore))
        count += 1

    global program_counter
    program_counter += 1
    return

def branch_instruction(binary_instruction):

    global program_counter

    op1 = int(binary_instruction[4:8], 2)
    op2 = int(binary_instruction[8:12], 2)
    pc_relative = int(binary_instruction[15:18], 2)

    registerFile = open("register_memory.txt", "r")  # open register file to hold values of registers in array
    all_registers = registerFile.readlines()  # registers

    val_in_op1 = int(all_registers[op1], 2)
    val_in_op2 = int(all_registers[op2], 2)

    registerFile.close()

    n = int(binary_instruction[12], 2)
    z = int(binary_instruction[13], 2)
    p = int(binary_instruction[14], 2)

    if(n == 0 & z == 1 & p == 0):
        print("BEQ R%d R%d %d" % (op1, op2, pc_relative))
    elif (n == 1 & z == 0 & p == 0):
        print("BLT R%d R%d %d" % (op1, op2, pc_relative))
    elif (n == 0 & z == 0 & p == 1):
        print("BGT R%d R%d %d" % (op1, op2, pc_relative))
    elif (n == 1 & z == 1 & p == 0):
        print("BLE R%d R%d %d" % (op1, op2, pc_relative))
    elif (n == 0 & z == 1 & p == 1):
        print("BGE R%d R%d %d" % (op1, op2, pc_relative))


    program_counter += pc_relative

    instruction_file = open("instruction_memory.txt", "r")
    all_instructions = instruction_file.readlines()
    instruction_file.close()

    instruction_file = open("instruction_memory.txt", "w")

    for line in all_instructions:

        if (int(line[0:10], 2) == program_counter):

            sentence = line[0:23] + str(n) + str(z) + str(p) + line[26:27] + '\n'
            instruction_file.write(sentence)
        else:
            instruction_file.write(line)


    return

def choose_instruction(binary_instruction):

    instruction_type = binary_instruction[0:4]
    inst = int(instruction_type, 2)

    switcher = {
        0: add_instruction,
        1: and_instruction,
        2: or_instruction,
        3: xor_instruction,
        4: addi_instruction,
        5: andi_instruction,
        6: ori_instruction,
        7: xori_instruction,
        8: jump_instruction,
        9: load_instruction,
        10: store_instruction,
        11: branch_instruction,
    }

    execute_func = switcher.get(inst)
    execute_func(binary_instruction)
    return

def start():

    instruction_file = open("instruction_memory.txt")
    all_instructions = instruction_file.readlines()

    global program_counter
    program_counter = 0

    count = -1
    for line in all_instructions:

        if(line == "\n"):
            continue

        count += 1

        if(count < program_counter):
            continue

        binary_instruction = line[0:18]

        choose_instruction(binary_instruction)



    return

start()