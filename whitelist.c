#include"antivirus.h"

int check_for_whitelist(char *filename)
{
	int err = 0,ret = 0, read_bytes = 0, virusflag =0, read_bytes1 = 0, i_size = 0, i_size1= 0;
	struct file *black_list= NULL, *white_list =NULL, *input_file = NULL;
	int file_seek_position = 0;
	char *black_list_buff = NULL, *virusname = NULL , *parse_virus= NULL, *input_file_buffer= NULL;
	
	white_list = filp_open("/etc/antivirusfiles/whitelist", O_RDONLY, 0);
        if(IS_ERR(white_list)) {
                printk("\nError white_list in file open");
		goto out;
        }

	input_file = filp_open(filename, O_RDONLY, 0);
        if(IS_ERR(input_file)) {
                printk("\nError in input file open");
		goto out;
        }

	input_file_buffer = kmalloc(PAGE_SIZE,GFP_KERNEL);
	if(input_file_buffer == NULL)
	{
		err = -ENOMEM;
		goto out;
	}

	i_size = i_size_read(file_inode(black_list));
	i_size1 = i_size_read(file_inode(input_file));
	
	while(i_size > 0 )
	{
		if(black_list_buff == NULL || strlen(black_list_buff) == 0)
		{		
			black_list_buff = kmalloc(PAGE_SIZE,GFP_KERNEL);
			read_bytes = read_file(black_list, &black_list_buff, 35);
			file_seek_position += remove_garbage_value(&black_list_buff, 35);
        		black_list->f_pos = file_seek_position;	
			i_size -= strlen(black_list_buff);	
		}
			
		parse_virus = strsep(&black_list_buff,"\n");
		
		virusname = strsep(&parse_virus,",");

		printk("\n Virus Name %s",virusname);

		printk("\n Virus content %s", parse_virus);
		
		/*while(i_size1 > 0 )
		{			
			input_file_buffer[0]='\0';
			read_bytes1 = read_file(input_file, input_file_buffer, 35);
			printk("\nInput_file_buffer -\n%s", input_file_buffer);			
			if(strstr(parse_virus,input_file_buffer)!= NULL)
			{
				printk("\t Virus file.");
				virusflag = 1;				
				goto out;				
			}	
			i_size1 -= read_bytes1;	
		}*/					
	}

	out:	
	if(virusflag == 1)
		//Code for rename file to .virus.
	if(black_list)	
		filp_close(black_list,NULL);	
	
	if(white_list)	
		filp_close(white_list,NULL);

	if(input_file)
		filp_close(input_file,NULL);	

	if(input_file_buffer)
		kfree(input_file_buffer);
	return err;
}



