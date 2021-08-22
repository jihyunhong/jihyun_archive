import mysql.connector

# TODO: REPLACE THE VALUE OF VARIABLE team (EX. TEAM 1 --> team = 1)
team = 1


# Requirement1: create schema ( name: DMA_team## )
def requirement1(host, user, password):
    cnx = mysql.connector.connect(host=host, user=user, password=password)
    cursor = cnx.cursor()
    cursor.execute('SET GLOBAL innodb_buffer_pool_size=2*1024*1024*1024;')

    # TODO: WRITE CODE HERE
    cursor.execute('CREATE DATABASE IF NOT EXISTS DMA_team01;')
    cursor.execute('USE DMA_team01;')

    # TODO: WRITE CODE HERE
    cursor.close()


# Requierement2: create table
def requirement2(host, user, password):
    cnx = mysql.connector.connect(host=host, user=user, password=password)
    cursor = cnx.cursor()
    cursor.execute('SET GLOBAL innodb_buffer_pool_size=2*1024*1024*1024;')

    # TODO: WRITE CODE HERE
    cursor.execute('CREATE DATABASE IF NOT EXISTS DMA_team01;')
    cursor.execute('USE DMA_team01;')
    
    # 1. user table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS USER(
    id BIGINT(20) NOT NULL,
    user_name VARCHAR(255) NOT NULL,
    profile TINYINT(1) NOT NULL,
    items_count INT(11) NOT NULL,
    PRIMARY KEY(id),
    UNIQUE(user_name));
    ''')
    
    # 2. item table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS ITEM(
    id BIGINT(20) NOT NULL,
    item_name VARCHAR(255) NOT NULL,
    price FLOAT,
    beta_version TINYINT(1) NOT NULL,
    ratings INT(11) NOT NULL,
    metascore INT(11) NOT NULL,
    developers VARCHAR(255),
    release_date DATE,
    PRIMARY KEY(id));
    ''')
    
    # 3. user_item table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS USER_ITEM(
    user_id BIGINT(20) NOT NULL,
    item_id BIGINT(20) NOT NULL,
    usagetime_2weeks INT(11) NOT NULL,
    usagetime_total INT(11) NOT NULL);
    ''')
    
    # 4. review table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS REVIEW(
    id VARCHAR(255) NOT NULL,
    user_id BIGINT(20) NOT NULL,
    item_id BIGINT(20) NOT NULL,
    recommend TINYINT(1) NOT NULL, 
    body INT(11) NOT NULL, 
    helpful_score FLOAT NOT NULL, 
    helpful_count INT(11) NOT NULL,
    posted_date DATE NOT NULL,
    PRIMARY KEY(id));
    ''')
    
    # 5. genre table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS GENRE(
    id VARCHAR(255) NOT NULL,
    genre_name VARCHAR(255) NOT NULL,
    PRIMARY KEY(id),
    UNIQUE(genre_name));
    ''')
    
    # 6. item_genre table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS ITEM_GENRE(
    item_id BIGINT(20) NOT NULL,
    genre_id VARCHAR(255) NOT NULL);
    ''')

    # 7. bundle table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS BUNDLE(
    id BIGINT(20) NOT NULL,
    bundle_name VARCHAR(255) NOT NULL,
    price FLOAT NOT NULL, 
    final_price FLOAT NOT NULL,
    discount FLOAT NOT NULL,
    PRIMARY KEY(id));
    ''')
    
    # 8. bundle_item table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS BUNDLE_ITEM(
    bundle_id BIGINT(20) NOT NULL,
    item_id BIGINT(20) NOT NULL);
    ''')
    
    # 9. bundle_genre table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS BUNDLE_GENRE(
    bundle_id BIGINT(20) NOT NULL,
    genre_id VARCHAR(255) NOT NULL,
    genre_count INT(11) NOT NULL);
    ''')
    
    # 10. tag --> UNIQUE(tag_name), tag_order NOT NULL 여부
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS TAG(
    item_id BIGINT(20) NOT NULL,
    tag_name VARCHAR(255) NOT NULL,
    tag_order INT(11) NOT NULL,
    PRIMARY KEY(item_id, tag_name));
    ''')
    
    # 11. item_specs
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS ITEM_SPECS(
    item_id BIGINT(20) NOT NULL,
    spec_name VARCHAR(255));
    ''')
    
    # TODO: WRITE CODE HERE
    cursor.close()

    
# Requirement3: insert data
def requirement3(host, user, password, directory):
    cnx = mysql.connector.connect(host=host, user=user, password=password)
    cursor = cnx.cursor()
    cursor.execute('SET GLOBAL innodb_buffer_pool_size=2*1024*1024*1024;')

    # TODO: WRITE CODE HERE
    cursor.execute('CREATE DATABASE IF NOT EXISTS DMA_team01;')
    cursor.execute('USE DMA_team01;')
    
    csv_dict = {'bundle_genre.csv': ['INT', 'VARCHAR', 'INT'],
                'bundle_item.csv': ['INT', 'INT'],
                'bundle.csv': ['INT', 'VARCHAR', 'FLOAT', 'FLOAT', 'FLOAT'],
                'genre.csv': ['VARCHAR', 'VARCHAR'],
                'item_genre.csv': ['INT', 'VARCHAR'],
                'item_specs.csv': ['INT', 'VARCHAR'],
                'item.csv': ['BIGINT', 'VARCHAR', 'FLOAT', 'TINYINT', 'INT', 'INT', 'VARCHAR', 'DATE'],
                'review.csv': ['VARCHAR', 'BIGINT', 'INT', 'TINYINT', 'INT', 'FLOAT', 'INT', 'DATE'],
                'tag.csv': ['INT', 'VARCHAR', 'INT'],
                'user_item.csv': ['BIGINT', 'INT', 'INT', 'INT'],
                'user.csv': ['BIGINT', 'VARCHAR', 'TINYINT', 'INT']}
    
    verbose = False # 'print'하려면, then set verbose=True
    
    for key in csv_dict.keys():
        if verbose:
            print(f'\n{key}')
        filepath = directory + '/' + key
        type_list = csv_dict[key] # list of datatype(ex: 'INT', 'FLOAT' etc. )
        
        with open(filepath, 'r', encoding='utf-8') as csv_data:
            
            for i, row in enumerate(csv_data.readlines()[1:]):
                if verbose:
                    print(f'{i}', end='\r')
                row = row.strip().split(',')
                # assert len(row) == len(type_list)  # debugging용
                
                for idx, r in enumerate(row):
                    if len(r) == 0: # r이 빈 string일 경우 'null' 입력
                        row[idx] = 'null'
                        continue
                    if key == 'item.csv' and r == 'nan': # item table에서 r이 nan일 경우 'null'입력
                        row[idx] = 'null'
                        continue
                    if type_list[idx] in ['TINYINT', 'INT', 'BIGINT']: # r이 정수면 int형으로
                        row[idx] = int(r)
                    elif type_list[idx] in ['FLOAT']: # r이 실수면 float형으로
                        try:
                            row[idx] = float(r)
                        except:
                            if r[-1] == '%': # 퍼센트 자료형의 경우 % 제거 후 실수로 변경
                                row[idx] = float(r[:-1])
                            elif r[0] == '$': # 가격의 경우 $제거 후 실수로 변경
                                row[idx] = float(r[1:])
                    elif type_list[idx] in ['VARCHAR', 'DATE']: # r이 문자열이면 string형으로
                        row[idx] = r
                    else:
                        raise ValueError
                
                row = tuple(row)
                sql = f"REPLACE INTO {key[:-4]} VALUES {row};"
                sql = sql.replace("'null'", 'null') # 사후처리 (‘null’ -> null 대체)
                cursor.execute(sql)

        cnx.commit() # 파일별로 commit(총 11번)

    # TODO: WRITE CODE HERE
    cursor.close()


# Requirement4: add constraint (foreign key)
def requirement4(host, user, password):
    cnx = mysql.connector.connect(host=host, user=user, password=password)
    cursor = cnx.cursor()
    cursor.execute('SET GLOBAL innodb_buffer_pool_size=2*1024*1024*1024;')

    # TODO: WRITE CODE HERE
    cursor.execute('CREATE DATABASE IF NOT EXISTS DMA_team01;')
    cursor.execute('USE DMA_team01;')
    
    # review의 FOREIGN KEY 설정
    cursor.execute('ALTER TABLE REVIEW ADD CONSTRAINT FOREIGN KEY(user_id) REFERENCES USER(id);')
    cursor.execute('ALTER TABLE REVIEW ADD CONSTRAINT FOREIGN KEY(item_id) REFERENCES ITEM(id);')
    
    # user_item의 FOREIGN KEY 설정
    cursor.execute('ALTER TABLE USER_ITEM ADD CONSTRAINT FOREIGN KEY(user_id) REFERENCES USER(id);')
    cursor.execute('ALTER TABLE USER_ITEM ADD CONSTRAINT FOREIGN KEY(item_id) REFERENCES ITEM(id);')
   
    # item_genre의 FOREIGN KEY 설정
    cursor.execute('ALTER TABLE ITEM_GENRE ADD CONSTRAINT FOREIGN KEY(item_id) REFERENCES ITEM(id);')
    cursor.execute('ALTER TABLE ITEM_GENRE ADD CONSTRAINT FOREIGN KEY(genre_id) REFERENCES GENRE(id);')

    # tag의 FOREIGN KEY 설정
    cursor.execute('ALTER TABLE TAG ADD CONSTRAINT FOREIGN KEY(item_id) REFERENCES ITEM(id);')
    
    # genre의 FOREIGN KEY 설정
    cursor.execute('ALTER TABLE BUNDLE_GENRE ADD CONSTRAINT FOREIGN KEY(genre_id) REFERENCES GENRE(id);')
    
    # bundle의 FOREIGN KEY 설정
    cursor.execute('ALTER TABLE BUNDLE_ITEM ADD CONSTRAINT FOREIGN KEY(bundle_id) REFERENCES BUNDLE(id);')
    
    # bundle_item의 FOREIGN KEY 설정
    cursor.execute('ALTER TABLE BUNDLE_ITEM ADD CONSTRAINT FOREIGN KEY(item_id) REFERENCES ITEM(id);')
    cursor.execute('ALTER TABLE BUNDLE_ITEM ADD CONSTRAINT FOREIGN KEY(bundle_id) REFERENCES BUNDLE(id);')
    
    # item_specs의 FOREIGN KEY 설정 
    cursor.execute('ALTER TABLE ITEM_SPECS ADD CONSTRAINT FOREIGN KEY(item_id) REFERENCES ITEM(id);')
    
    cnx.commit()
    
    # TODO: WRITE CODE HERE
    cursor.close()


# TODO: REPLACE THE VALUES OF FOLLOWING VARIABLES
host = 'localhost'
user = 'root'
password = ''
directory = './dataset'

requirement1(host=host, user=user, password=password)
requirement2(host=host, user=user, password=password)
requirement3(host=host, user=user, password=password, directory=directory)
requirement4(host=host, user=user, password=password)