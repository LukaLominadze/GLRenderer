import subprocess
import platform
import os

current_dir = os.path.dirname(os.path.abspath(__file__))
solution_dir = os.path.join(current_dir, '../../../')

batch_file = os.path.join(current_dir, 'premake5.bat')

if platform.system() == 'Windows':
    try:
        subprocess.call([batch_file], cwd=current_dir)

        vcxproj_glcore = os.path.join(solution_dir, 'GLRenderer/GLRenderer.vcxproj')
        vcxproj_gltest = os.path.join(solution_dir, 'GLTest/GLTest.vcxproj')

        insert_count = 0
        glcore_guid = ''

        print('\nAttempting to retrieve "GLCore" GUID...')
        with open(vcxproj_glcore, "r") as f:
            lines = f.readlines()

            for i, line in enumerate(lines):    
                if "<ProjectGuid>" in line:
                    glcore_guid = line.strip().lstrip('<ProjectGuid>{').rstrip('}</ProjectGuid>').lower()
                    insert_count += 1
                    print('Success! -> ' + glcore_guid)
                    insert_count += 1
                if '<ClCompile Include="src\\glpch.cpp"' in line:
                    lines.insert(i + 1, "\t\t\t<PrecompiledHeader Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">Create</PrecompiledHeader>\n" +
                                        "\t\t\t<PrecompiledHeader Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">Create</PrecompiledHeader>\n")
                    insert_count += 1
                if insert_count == 2:
                    break
        
        f.close()

        print('\nAttempting to set reference to "GLCore" in "GLTest"...')
        with open(vcxproj_gltest, "r") as f1:
            lines1 = f1.readlines()

            for j, line in enumerate(lines1):
                if '<Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />' in line:
                    lines1.insert(j, '\t<ItemGroup>\n\t\t<ProjectReference Include="..\\GLRenderer\\GLRenderer.vcxproj">\n\t\t\t<Project>{' + glcore_guid + '}</Project>\n\t\t</ProjectReference>\n\t</ItemGroup>\n')
                    break
        
        with open(vcxproj_gltest, "w") as f1:
            f1.writelines(lines1)

        print('Success!\n')
    except subprocess.CalledProcessError as e:
        print("Script failed! --- ", e)

input('Press press ENTER to end setup...')
