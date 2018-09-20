import os

code_path, files_path = [0, 0]

def execute(filename):
	global code_path, files_path
	output = filename + '_stdout'
	diff_output = filename + '_diff_stdout'
	run = 'python3' + ' ' + code_path + ' < ' + files_path + 'input/' + filename + ' > ' + output
	#  run = code_path + ' < ' + files_path + 'input/' + filename + ' > ' + output
	check = 'diff' + ' ' + output + ' ' + files_path + 'output/' + filename + ' > ' + diff_output
	os.system(run)
	os.system(check)
	if os.stat(diff_output).st_size != 0:
		print('Deu ruim no' + ' ' + filename)
	os.system('rm ' + output + ' ' + diff_output)

def main():
	global code_path, files_path
	code_path = '\"' + input() + '\"'
	files_path = '\"' + input() + '\"'
	cmd = 'ls' + ' ' + files_path + 'input/' ' > output'
	os.system(cmd)
	with open('output', 'r') as f:
		for i in f.readlines():
			execute(i.strip())

main()