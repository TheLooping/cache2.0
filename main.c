#include "my_memory_pool.h"
#include "my_cache_strategy.h"
#include "my_forward.h"
#include "my_cache.h"
#include <stdio.h>
#define REQUEST_SIZE 0 * GB + 0 * MB + 1 * KB + 0 * 1



int main()
{
    char *buffer = malloc(sizeof(char) * 1024);
    memory_pool_t *mp = memory_pool_t_init(REQUEST_SIZE);
    
    uint32_t len;
    char *str = (char *)malloc(sizeof(char) * len);



    key_value_pair_t *kv = (key_value_pair_t *)malloc(sizeof(key_value_pair_t));
    while (1)
    {
        len = 1024;
        fgets(str, len, stdin);
        // 判读是否退出
        if (str[0] == 'e' && str[1] == 'x' && str[2] == 'i' && str[3] == 't' && str[3] == 't')
        {
            break;
        }
        len = strlen(str);// 获取输入字符串长度
        store_key_value_pair(mp, str, len);

    }

    // 输出内存池信息
    // 输出到文件
    FILE *fp = fopen("output2.txt", "w");
    if(fp == NULL)
    {
        printf("open file failed!\n");
        return 0;
    }
    if (fp == NULL)
    {
        printf("open file failed!\n");
        return 0;
    }
    if (fprintf(fp, "写入文件内容") < 0) {
        perror("写入文件时发生错误");
        fclose(fp);
        return 1;
    }
    {
        fprintf(fp, "------------------------------------------memory_pool_t------------------------------------\n");
        fprintf(fp, "memory_pool_t_size: %lu\n", mp->memory_pool_t_size);
        fprintf(fp, "num_total_chunk: %ld\n", mp->num_total_chunk);
        fprintf(fp, "num_free_chunk: %ld\n", mp->num_free_chunk);
        fprintf(fp, "num_total_key_value_pair: %ld\n", mp->num_total_key_value_pair);
        fprintf(fp, "num_free_key_value_pair: %ld\n", mp->num_free_key_value_pair);
        fprintf(fp, "memory_pool_t_start: %p\n", mp->memory_pool_t_start); // %p输出指针地址
        fprintf(fp, "hash_table_start: %p\n", mp->hash_table_start);
        fprintf(fp, "chunk_header_start: %p\n", mp->chunk_header_start);
        fprintf(fp, "chunks_start: %p\n", mp->chunks_start);
        fprintf(fp, "key_value_pair_table_free_list: %p\n", mp->key_value_pair_table_free_list);
        fprintf(fp, "key_value_pair_table_alloc_list: %p\n", mp->key_value_pair_table_alloc_list);
        fprintf(fp, "free_list: %p\n", mp->free_list);
        fprintf(fp, "alloc_list: %p\n", mp->alloc_list);
    }
    // 输出整个内存池
    {
        fprintf(fp, "\n\n\n-----------------------------");
        fprintf(fp, "\n--------memory_pool_t--------");
        fprintf(fp, "\n-----------------------------\n");
        // 每条key-value pair

        key_value_pair_t *kv = mp->key_value_pair_table_alloc_list;
        for (int i = 0; i < mp->num_total_key_value_pair - mp->num_free_key_value_pair; i++)
        {
            if (kv->is_alloc == 1)
            {
                fprintf(fp, "\n\n\n------------------------------------------key_value_pair(%d)------------------------------------\n",i+1);
                fprintf(fp, "id: %d - ", kv->id);
                fprintf(fp, "is_alloc: %d - ", kv->is_alloc);
                fprintf(fp, "pirority: %d - ", kv->pirority);
                fprintf(fp, "value_start: %p - ", kv->value_start);
                fprintf(fp, "value_size: %lu - ", kv->value_size);
                fprintf(fp, "key: %lu - ", kv->key);
                fprintf(fp, "start_chunk_id: %ld - ", kv->start_chunk_id);
                fprintf(fp, "num_chunk: %ld\n", kv->num_chunk);
                fprintf(fp, "self: %p - ", kv);
                fprintf(fp, "prev: %p - ", kv->prev);
                fprintf(fp, "next: %p\n", kv->next);
                // 对应所有chunk块

                chunk_header_t *ch = (chunk_header_t *)(mp->chunk_header_start + kv->start_chunk_id * sizeof(chunk_header_t));
                for (int j = 0; j < kv->num_chunk; j++)
                {
                    fprintf(fp, "\n- - - - - - - - - - chunk(%d) - - - - - - - - - - - -\n",j+1);
                    fprintf(fp, "chunk_id: %d - ", ch->chunk_id);
                    fprintf(fp, "is_alloc: %d - ", ch->is_alloc);
                    fprintf(fp, "chunk_start: %p - ", ch->chunk_start);
                    fprintf(fp, "self: %d - ", ch->chunk_id);
                    fprintf(fp, "prev: %d - ", ch->prev->chunk_id);
                    fprintf(fp, "next: %d\n", ch->next->chunk_id);
                    fprintf(fp, "%d/%d chunk:", j+1, kv->num_chunk);
                    fwrite(ch->chunk_start, 1, CHUNK_SIZE, fp);
                    ch = ch->next;
                }
            }
            kv = kv->next;
        }
    }

    return 0;
}

// 造包程序
void make_request_data(char *buffer)
{
    memset(buffer, 0, sizeof(char) * 1024);
    request_t *request;
    request = (request_t *)buffer;    
    strcpy(request->key, "AAAA");
    request->tsb = 0;
    request->capacity = 0;
}

void make_response_data(char *buffer)
{
    memset(buffer, 0, sizeof(char) * 1024);
    forward_data_t *response;
    response = (forward_data_t *)buffer;
    response->tsb = 0;
    response->tsi = 5;// 假设路径总跳数为5
    response->len = 100;
    response->start = response + sizeof(forward_data_t);
    response->remainCapacity = 0;
    strcpy(response->start, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
}