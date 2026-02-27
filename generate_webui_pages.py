import json
import glob

project_folder = "./irRemoteESP32/"

gen_config_files = glob.glob(f"{project_folder}/*.json")

for gen_config_file in gen_config_files:
    with open(gen_config_file, "r") as f:
        gen_config = json.load(f)
    filename_html   = gen_config["webui"]["filename_html"]
    filename_h      = gen_config["webui"]["filename_h"]
    htmlstring_name = gen_config["webui"]["htmlstring_name"]
    h_guard_block   = gen_config["webui"]["h_guard_block"]

    with open(f"{project_folder}/{filename_html}", "r", encoding="utf-8") as fin:
        with open(f"{project_folder}/{filename_h}", "w", encoding="utf-8") as fout:
            html_string = r"\n".join([l.strip().replace('"', r'\"') for l in fin.readlines()])
            fout.write(f"#ifndef {h_guard_block}\n")
            fout.write(f"#define {h_guard_block}\n")
            fout.write(f"const char* {htmlstring_name} = \"{html_string}\";\n")
            fout.write(f"#endif\n")
