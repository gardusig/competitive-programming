def build_config():
	global config
	filename = 'config.txt'
	with open(filename, 'r') as config_file:
		v = config_file.readlines()
		config = {
			'code_path': get_config(v[0]),
			'stdin_path': get_config(v[1]),
			'stdout_path': get_config(v[2]),
			'timeout': float(get_config(v[3]))
		}
		config['language'] = get_language(config['code_path'])
		if config['language'] == None:
			print('language of ' + '\"' + config['code_path'] + '\"' + ' is not known')
			exit(1)
		from os import walk
		config['filenames'] = []
		for (dirpath, dirnames, filenames) in walk(config['stdin_path']):
			config['filenames'].extend(filenames)
		config['filenames'].sort()

def build_languages():
	global languages
	languages = {
		'c': {
			'suffix': 'c',
			'compile': ['gcc', '-O4', '-lm'],
			'run': './',
		},
		'c++': {
			'suffix': 'cpp',
			'compile': ['g++', '-std=c++11', '-O4', '-lm'],
			'run': './',
		},
		'java': {
			'suffix': 'java',
			'compile': ['javac'],
			'run': 'java ',
		},
		'python': {
			'suffix': 'py',
			'compile': None,
			'run': 'python3 ',
		}
	}

def build_program():
	if languages[config['language']]['compile'] == None:
		print('does not need to compile code in ' + '\"' + config['language'] + '\"' + ' language')
	else:
		import subprocess
		print('compiling code in ' + '\"' + config['language'] + '\"' + ' language')
		subprocess.run([*languages[config['language']]['compile'], config['code_path']])
		config['code_path'] = 'a.out'

def get_config(s):
	return s.split('"')[1].strip()

def get_language(s):
	for language in languages:
		if s.endswith(languages[language]['suffix']):
			return language
	return None

def run_program():
	import subprocess
	for filename in config['filenames']:
		try:
			with open(config['stdin_path'] + filename) as stdin:
				print('running file: ' + '\"' + filename + '\"')
				program = subprocess.run([languages[config['language']]['run'] + config['code_path']], stdin = stdin, stdout = subprocess.PIPE, stderr = subprocess.STDOUT, timeout = config['timeout'])
				output = program.stdout.decode('utf-8').strip()
				correct = ''
				with open(config['stdout_path'] + filename) as stdout:
					for line in stdout.readlines():
						correct += ('\n' if len(correct) > 0 else '') + line.strip()
				if correct != output:
					print('wrong answer in: ' + '\"' + filename + '\"')
					print('output:')
					print(output)
					print('correct:')
					print(correct)
					exit(0)
				print('correct!')
		except Exception as e:
			print(e)
			if type(e) is subprocess.TimeoutExpired:
				print('time limit exceeded in: ' + '\"' + filename + '\"')
			elif type(e) is subprocess.CalledProcessError:
				print('runtime error in: ' + '\"' + filename + '\"')
			exit(0)
	print('* accepted *')

def main():
	build_languages()
	build_config()
	build_program()
	run_program()

main()