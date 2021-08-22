# TODO: CHANGE THIS FILE NAME TO DMA_project2_team##.py
# EX. TEAM 1 --> DMA_project2_team01.py

# TODO: IMPORT LIBRARIES NEEDED FOR PROJECT 2
import mysql.connector
import os
import surprise
from surprise import Dataset
from surprise import Reader
from surprise.model_selection import KFold
from collections import defaultdict
import numpy as np
import pandas as pd
from sklearn import tree
import graphviz
from mlxtend.frequent_patterns import association_rules, apriori
import csv

np.random.seed(0)

# TODO: CHANGE GRAPHVIZ DIRECTORY
os.environ["PATH"] += os.pathsep + 'C:/Program Files/Graphviz/bin/'
# os.environ["PATH"] += os.pathsep + '/usr/local/Cellar/graphviz/2.47.1/bin/' # for MacOS

# TODO: CHANGE MYSQL INFORMATION, team number 
HOST = 'localhost'
USER = 'root'
PASSWORD = 'Poi946060@!'
SCHEMA = 'dma_team06'
team = 6


# PART 1: Decision tree 
def part1():
    cnx = mysql.connector.connect(host=HOST, user=USER, password=PASSWORD)
    cursor = cnx.cursor()
    cursor.execute('SET GLOBAL innodb_buffer_pool_size=2*1024*1024*1024;')
    cursor.execute('USE %s;' % SCHEMA)

    # TODO: Requirement 1-1. MAKE best_item column
    # item table에 best_item column 추가 // try-except 예외처리 : mysql에서 alter tabel drop column if exists 구문이 실행X
    print('Adding best_item column...')
    try:
        cursor.execute('ALTER TABLE item DROP COLUMN best_item')
    except:
        print('there is no best_item column')

    print("done")

    cursor.execute('ALTER TABLE item ADD best_item TINYINT(1) DEFAULT 0')

    # best_item_list.txt에서 data insert
    print('Inserting best_item list...')
    filepath = 'C:/Users/Administrator/Desktop/DMA_project2/best_item_list.txt'
    with open(filepath, 'r', encoding='utf-8') as temp:
        temp_lines = temp.readlines()  ## n-1의 index를 가진 best_item_list
        best_items = []
        for line in temp_lines:
            best_items.append(line)  ## line의 마지막 공백 제거 후 lines에 추가

    result_insert = []
    for best_item_id in best_items:
        # cursor.execute('UPDATE item SET best_item = 1')
        cursor.execute('UPDATE item SET best_item=1 WHERE id=' + best_item_id)
    print("done")

    # TODO: Requirement 1-2. WRITE MYSQL QUERY AND EXECUTE. SAVE to .csv file
    print('Making training csv...')
    fopen = open('DMA_project2_team%02d_part1.csv' % team, 'w', encoding='utf-8')
    cursor.execute('''
    SELECT id, best_item, ratings, num_of_specs, num_of_tags ,num_of_users, avg_usage_time,
    num_of_reviews, sum_of_recommend, avg_review_len
    FROM item
        NATURAL JOIN (SELECT item.id, COUNT(item_specs.spec_name) AS num_of_specs
            FROM item LEFT JOIN item_specs ON item.id=item_specs.item_id GROUP BY id)a

        NATURAL JOIN (SELECT item.id, COUNT(tag.tag_order) AS num_of_tags
            FROM item LEFT JOIN tag ON item.id=tag.item_id GROUP BY id)b

        NATURAL JOIN (SELECT item.id, COUNT(user_item.user_id) AS num_of_users
            FROM item LEFT JOIN user_item ON item.id=user_item.item_id GROUP BY id)c

        NATURAL JOIN (SELECT item.id, AVG(user_item.usagetime_total) AS avg_usage_time
            FROM item LEFT JOIN user_item ON item.id = user_item.item_id GROUP BY id)d

        NATURAL JOIN (SELECT item.id, COUNT(review.id) AS num_of_reviews
            FROM item LEFT JOIN review ON item.id=review.item_id GROUP BY id)e

        NATURAL JOIN (SELECT item.id, SUM(review.recommend) AS sum_of_recommend
            FROM item LEFT JOIN review ON item.id=review.item_id GROUP BY id)f

        NATURAL JOIN (SELECT item.id, AVG(review.body) AS avg_review_len
            FROM item LEFT JOIN review ON item.id=review.item_id GROUP BY id)g
    ''')

    rows = cursor.fetchall()
    writer = csv.writer(fopen, lineterminator='\n')
    writer.writerow(['id', 'best_item', 'ratings', 'num_of_specs', 'num_of_tags', 'num_of_users', 'avg_usage_time', \
                     'num_of_reviews', 'sum_of_recommend', 'avg_review_len'])
    for row in rows:
        print(row)
        writer.writerow(row)

    fopen.close()
    print('done')

    # TODO: Requirement 1-3. MAKE AND SAVE DECISION TREE
    # gini file name: DMA_project2_team##_part1_gini.pdf
    # entropy file name: DMA_project2_team##_part1_entropy.pdf
    print('Making training data...')
    filepath = 'C:/Users/Administrator/Desktop/DMA_project2/DMA_project2_team06_part1.csv'  ## 요거 컴퓨터마다 수정필요
    data = pd.read_csv(filepath)
    df = pd.DataFrame(data)

    classes = []
    features = []

    feature_df = df[['ratings', 'num_of_specs', 'num_of_tags', 'num_of_users', 'avg_usage_time', \
                     'num_of_reviews', 'sum_of_recommend', 'avg_review_len']]
    classes_df = df[['best_item']]

    for data in classes_df.values:
        classes.append(data[0])
    for row in feature_df.values.tolist():
        features.append(row)

    DT_gini = tree.DecisionTreeClassifier(criterion='gini', max_depth=5, min_samples_leaf=10)
    DT_gini.fit(X=features, y=classes)
    graph_gini = tree.export_graphviz(DT_gini, \
                                      out_file=None, \
                                      feature_names=['ratings', 'num_of_specs', 'num_of_tags', 'num_of_users', \
                                                     'avg_usage_time', 'num_of_reviews', 'sum_of_recommend', \
                                                     'avg_review_len'], class_names=['normal', 'BEST'])
    graph_gini = graphviz.Source(graph_gini)
    graph_gini.render('DMA_project2_team06_part1_gini', view=True)

    DT_entropy = tree.DecisionTreeClassifier(criterion='entropy', max_depth=5, min_samples_leaf=10)
    DT_entropy.fit(X=features, y=classes)
    graph_entropy = tree.export_graphviz(DT_entropy, \
                                         out_file=None, \
                                         feature_names=['ratings', 'num_of_specs', 'num_of_tags', 'num_of_users', \
                                                        'avg_usage_time', 'num_of_reviews', 'sum_of_recommend', \
                                                        'avg_review_len'], class_names=['normal', 'BEST'])
    graph_entropy = graphviz.Source(graph_entropy)
    graph_entropy.render('DMA_project2_team06_part1_entropy', view=True)

    # TODO: Requirement 1-4. Don't need to append code for 1-4

    cursor.close()


def part2():
    cnx = mysql.connector.connect(host=HOST, user=USER, password=PASSWORD)
    cursor = cnx.cursor()
    cursor.execute('SET GLOBAL innodb_buffer_pool_size=2*1024*1024*1024;')
    cursor.execute('USE %s;' % SCHEMA)

    # TODO: Requirement 2-1. CREATE VIEW AND SAVE to .csv file
    print('Making bundle.csv...')
    fopen = open('DMA_project2_team%02d_part2_bundle.csv' % team, 'w', encoding='utf-8')

    cursor.execute('DROP VIEW IF EXISTS bundle_score;')
    cursor.execute('''    
    CREATE VIEW bundle_score AS
        SELECT 
            a.bundle_id,
            bundle_name,
            num_item,
            IFNULL(num_genre, 0) AS num_genre,
            num_user,
            (num_item + IFNULL(num_genre, 0) + num_user) AS score
        FROM
            (SELECT 
                id AS bundle_id, bundle_name
            FROM
                bundle) a
                NATURAL JOIN
            (SELECT 
                bundle_id, COUNT(item_id) * 100 AS num_item
            FROM
                bundle_item
            GROUP BY bundle_id) b
                NATURAL JOIN
            (SELECT 
                bundle_id, (COUNT(user_id) / COUNT(DISTINCT d.item_id)) AS num_user
            FROM
                bundle_item d, user_item e
            WHERE
                d.item_id = e.item_id
            GROUP BY bundle_id) c
                LEFT JOIN
            (SELECT 
                bundle_id, COUNT(DISTINCT genre_id) * 100 AS num_genre
            FROM
                bundle_genre
            GROUP BY bundle_id) f ON a.bundle_id = f.bundle_id
        ORDER BY score DESC
        LIMIT 30
        ;
    ''')

    cursor.execute('SELECT * FROM bundle_score')
    writer = csv.writer(fopen, lineterminator='\n')
    writer.writerow(['bundle_id', 'bundle_name', 'num_item', 'num_genre', 'num_user', 'score'])

    for row in cursor:
        # print(row)
        writer.writerow(row)

    fopen.close()
    print('Done!')

    # TODO: Requirement 2-2. CREATE 2 VIEWS AND SAVE partial one to .csv file
    print('Making UBR.csv...')
    fopen = open('DMA_project2_team%02d_part2_UBR.csv' % team, 'w', encoding='utf-8')

    cursor.execute('DROP VIEW IF EXISTS user_bundle_rating;')
    cursor.execute('''
    CREATE VIEW user_bundle_rating AS
        SELECT 
            IFNULL(user_idA, user_idB) AS user,
            IFNULL(bundle_nameA, bundle_nameB) AS bundle,
            IFNULL(cnt_rec, 0) * 5 + IF(IFNULL(cnt_use, 0) < 5,
                IFNULL(cnt_use, 0),
                5) AS rating
        FROM
            (SELECT 
                *
            FROM
                (SELECT 
                user_id AS user_idA,
                    bundle_id AS bundle_idA,
                    bundle_name AS bundle_nameA,
                    COUNT(item_id) AS cnt_rec
            FROM
                bundle_score
            NATURAL JOIN bundle_item
            NATURAL JOIN review
            WHERE
                recommend = 1
            GROUP BY user_id , bundle_id) a
            LEFT JOIN (SELECT 
                user_id AS user_idB,
                    bundle_id AS bundle_idB,
                    bundle_name AS bundle_nameB,
                    COUNT(item_id) AS cnt_use
            FROM
                bundle_score
            NATURAL JOIN bundle_item
            NATURAL JOIN user_item
            GROUP BY user_id , bundle_id) b ON a.user_idA = b.user_idB
                AND a.bundle_idA = b.bundle_idB UNION SELECT 
                *
            FROM
                (SELECT 
                user_id AS user_idA,
                    bundle_id AS bundle_idA,
                    bundle_name AS bundle_nameA,
                    COUNT(item_id) AS cnt_rec
            FROM
                bundle_score
            NATURAL JOIN bundle_item
            NATURAL JOIN review
            WHERE
                recommend = 1
            GROUP BY user_id , bundle_id) a
            RIGHT JOIN (SELECT 
                user_id AS user_idB,
                    bundle_id AS bundle_idB,
                    bundle_name AS bundle_nameB,
                    COUNT(item_id) AS cnt_use
            FROM
                bundle_score
            NATURAL JOIN bundle_item
            NATURAL JOIN user_item
            GROUP BY user_id , bundle_id) b ON a.user_idA = b.user_idB
                AND a.bundle_idA = b.bundle_idB) d;
    ''')

    cursor.execute('DROP VIEW IF EXISTS partial_user_bundle_rating;')
    cursor.execute('''
    CREATE VIEW partial_user_bundle_rating AS
    SELECT 
        *
    FROM
        user_bundle_rating
            NATURAL JOIN
        (SELECT 
            user
        FROM
            user_bundle_rating
        GROUP BY user
        HAVING COUNT(*) >= 20) a;
    ''')

    cursor.execute('SELECT * FROM partial_user_bundle_rating')
    writer = csv.writer(fopen, lineterminator='\n')
    writer.writerow(['user', 'bundle', 'rating'])

    for row in cursor:
        # print(row)
        writer.writerow(row)

    fopen.close()
    print('Done!')

    # TODO: Requirement 2-3. MAKE HORIZONTAL VIEW
    # file name: DMA_project2_team##_part2_horizontal.pkl
    # use to_pickle(): df.to_pickle(filename)
    print('Making horizontal.pkl ...')
    cursor.execute('SELECT * FROM partial_user_bundle_rating')
    df = pd.DataFrame(cursor.fetchall())
    df.columns = cursor.column_names
    df = df.set_index('user')

    df['rating'] = df['rating'] / df['rating']
    #     print(df)
    hor_view = pd.pivot_table(df, index='user', columns='bundle', values='rating', fill_value=0)
    #     print(hor_view)

    filename = 'DMA_project2_team06_part2_horizontal.pkl'
    hor_view.to_pickle(filename)
    print('Done!')

    # TODO: Requirement 2-4. ASSOCIATION ANALYSIS
    # filename: DMA_project2_team##_part2_association.pkl (pandas dataframe)
    print('Making association.pkl ...')


    frequent_itemsets = apriori(hor_view, min_support = 0.35, use_colnames = True)
    # # #     print(frequent_itemsets)

    rules = association_rules(frequent_itemsets, metric = 'lift', min_threshold = 2)
    # # #     print(rules.to_string())

    filename = 'DMA_project2_team06_part2_association.pkl'
    rules.to_pickle(filename)
    print('Done!')
    cursor.close()

# PART 3:
# TODO: Requirement 3-1. WRITE get_top_n
def get_top_n(algo, testset, id_list, n, user_based=True):
    results = defaultdict(list)

    if user_based:
        # TODO: testset의 데이터 중에 user id가 id_list 안에 있는 데이터만 따로 testset_id로 저장
        # Hint: testset은 (user_id, bundle_name, default_rating)의 tuple을 요소로 갖는 list

        testset_id = []
        print("makes a testset_id list...")
        for i in testset:
            if i[0] in id_list:
                testset_id.append(i)
            else:
                pass

        predictions = algo.test(testset_id)
        print("make a prediction results...")

        # TODO: results는 user_id를 key로, [(bundle_name, estimated_rating)의 tuple이 모인 list]를 value로 갖는 dictionary
        for uid, bname, true_r, est, _ in predictions:
            results[uid].append((bname, est))

    else:
        # TODO: testset의 데이터 중 bundle name이 id_list 안에 있는 데이터만 따로 testset_id라는 list로 저장
        # Hint: testset은 (user_id, bundle_name, default_rating)의 tuple을 요소로 갖는 list

        testset_id = []
        print("make a testset_id list...")
        for i in testset:
            if i[1] in id_list:
                testset_id.append(i)
            else:
                pass

        predictions = algo.test(testset_id)
        print("make a prediction results...")

        # TODO: results는 bundle_name를 key로, [(user_id, estimated_rating)의 tuple이 모인 list]를 value로 갖는 dictionary
        for uid, bname, true_r, est, _ in predictions:
            results[bname].append((uid, est))

    # TODO: rating 순서대로 정렬하고 top-n개만 유지
    print("sort for rating...")
    new_result = {}

    for id_, ratings in results.items():
        ratings.sort(key=lambda x: x[1], reverse=True)
        top_ratings = list(ratings[:n])
        new_result[id_] = top_ratings
    results = new_result

    return results

# PART 3. Requirement 3-2, 3-3, 3-4
def part3():
    file_path = 'DMA_project2_team%02d_part2_UBR.csv' % team
    reader = surprise.Reader(line_format='user item rating', sep=',', rating_scale=(1, 10), skip_lines=1)
    data = surprise.Dataset.load_from_file(file_path, reader=reader)

    trainset = data.build_full_trainset()
    testset = trainset.build_anti_testset()

    print("start user-based recommendation...")
    # TODO: Requirement 3-2. User-based Recommendation
    uid_list = ['8051826169', '8027368512', '7998746368', '8054453794', '8030770479']

    # TODO: set algorithm for 3-2-1
    sim_options = {'name': 'cosine', 'user_based': True}
    algo = surprise.prediction_algorithms.knns.KNNBasic(sim_options=sim_options)
    algo.fit(trainset)
    results = get_top_n(algo, testset, uid_list, n=5, user_based=True)
    with open('3-2-1.txt', 'w') as f:
        for uid, ratings in sorted(results.items(), key=lambda x: x[0]):
            f.write('User ID %s top-5 results\n' % uid)
            for bname, score in ratings:
                f.write('Bundle NAME %s\n\tscore %s\n' % (bname, str(score)))
            f.write('\n')
    print("3-2-1 done")

    # TODO: set algorithm for 3-2-2
    sim_options = {'name': 'pearson', 'user_based': True}
    algo = surprise.prediction_algorithms.knns.KNNWithMeans(sim_options=sim_options)
    algo.fit(trainset)
    results = get_top_n(algo, testset, uid_list, n=5, user_based=True)
    with open('3-2-2.txt', 'w') as f:
        for uid, ratings in sorted(results.items(), key=lambda x: x[0]):
            f.write('User ID %s top-5 results\n' % uid)
            for bname, score in ratings:
                f.write('Bundle NAME %s\n\tscore %s\n' % (bname, str(score)))
            f.write('\n')
    print("3-2-2 done")

    # TODO: 3-2-3. Best Model
    print("This is best model")
    sim_options = {'name': 'pearson_baseline', 'user_based': True}
    bsl_options = {'method': 'als', 'n_epochs': 5, 'reg_u': 10, 'reg_i': 5}
    best_algo_ub = surprise.KNNBaseline(sim_options=sim_options, bsl_options=bsl_options)
    best_algo_ub.fit(trainset)
    results = get_top_n(best_algo_ub, testset, uid_list, n=5, user_based=True)
    print(results)

    print("Cross validation...")
    np.random.seed(0)
    kf = surprise.model_selection.split.KFold(n_splits=5, random_state=0)

    KBs_sim_list = ['cosine', 'pearson', 'MSD', 'pearson_baseline']
    KBs_mean_acc_list = []

    for x in KBs_sim_list:
        acc = []
        sim_options = {'name': x, 'user_based': True}
        algo = surprise.KNNBasic(sim_options=sim_options)

        for i, (trainset, testset) in enumerate(kf.split(data)):
            algo.fit(trainset)
            predictions = algo.test(testset)
            acc.append(surprise.accuracy.rmse(predictions, verbose=True))
        A = np.mean(acc)
        KBs_mean_acc_list.append(A)
    print("KNNBasic Done")

    KW_sim_list = ['cosine', 'pearson', 'MSD', 'pearson_baseline']
    KW_mean_acc_list = []

    for x in KW_sim_list:
        acc = []
        sim_options = {'name': x, 'user_based': True}
        algo = surprise.KNNWithMeans(sim_options=sim_options)

        for i, (trainset, testset) in enumerate(kf.split(data)):
            algo.fit(trainset)
            predictions = algo.test(testset)
            acc.append(surprise.accuracy.rmse(predictions, verbose=True))
        A = np.mean(acc)
        KW_mean_acc_list.append(A)
    print("KNNWithbasic Done")

    KBl_list = [(5, 10, 5), (10, 20, 15), (20, 30, 20)]
    KBl_mean_acc_list = []

    for x, y, z in KBl_list:
        acc = []
        sim_options = {'name': 'pearson_baseline', 'user_based': True}
        bsl_options = {'method': 'als', 'n_epochs': x, 'reg_u': y, 'reg_i': z}
        algo = surprise.KNNBaseline(sim_options=sim_options, bsl_options=bsl_options)

        for i, (trainset, testset) in enumerate(kf.split(data)):
            algo.fit(trainset)
            predictions = algo.test(testset)
            acc.append(surprise.accuracy.rmse(predictions, verbose=True))
        A = np.mean(acc)
        KBl_mean_acc_list.append(A)
    print("KNNBaseline Done")

    print(KBs_mean_acc_list)
    print(KW_mean_acc_list)
    print(KBl_mean_acc_list)

    trainset = data.build_full_trainset()
    testset = trainset.build_anti_testset()

    print("start item-based recommendation...")
    # TODO: Requirement 3-3. Item-based Recommendation
    bname_list = ['World of Magicka Bundle',
                  'Borderlands Triple Pack',
                  'Tripwire Complete Bundle',
                  'Grand Theft Auto V & Great White Shark Cash Card',
                  'Killing Floor 1 Complete Your Set!']

    # TODO - set algorithm for 3-3-1
    sim_options = {'name': 'cosine', 'user_based': False}
    algo = surprise.prediction_algorithms.knns.KNNBasic(sim_options=sim_options)
    algo.fit(trainset)
    results = get_top_n(algo, testset, bname_list, n=10, user_based=False)
    with open('3-3-1.txt', 'w') as f:
        for bname, ratings in sorted(results.items(), key=lambda x: x[0]):
            f.write('Bundle NAME %s top-10 results\n' % bname)
            for uid, score in ratings:
                f.write('User ID %s\n\tscore %s\n' % (uid, str(score)))
            f.write('\n')
    print("3-3-1 done")

    # TODO: set algorithm for 3-3-2
    sim_options = {'name': 'pearson', 'user_based': False}
    algo = surprise.prediction_algorithms.knns.KNNWithMeans(sim_options=sim_options)
    algo.fit(trainset)
    results = get_top_n(algo, testset, bname_list, n=10, user_based=False)
    with open('3-3-2.txt', 'w') as f:
        for bname, ratings in sorted(results.items(), key=lambda x: x[0]):
            f.write('Bundle NAME %s top-10 results\n' % bname)
            for uid, score in ratings:
                f.write('User ID %s\n\tscore %s\n' % (uid, str(score)))
            f.write('\n')
    print("3-3-2 done")

    # TODO: 3-3-3. Best Model
    print("This is best model")
    sim_options = {'name': 'pearson', 'user_based': False}
    best_algo_ib = surprise.KNNWithMeans(sim_options=sim_options)
    best_algo_ib.fit(trainset)
    results = get_top_n(best_algo_ib, testset, bname_list, n=5, user_based=False)
    print(results)

    print("Cross validation...")
    np.random.seed(0)
    kf = surprise.model_selection.split.KFold(n_splits=5, random_state=0)

    KBs_sim_list = ['cosine', 'pearson', 'MSD', 'pearson_baseline']
    KBs_mean_acc_list2 = []

    for x in KBs_sim_list:
        acc = []
        sim_options = {'name': x, 'user_based': False}
        algo = surprise.KNNBasic(sim_options=sim_options)

        for i, (trainset, testset) in enumerate(kf.split(data)):
            algo.fit(trainset)
            predictions = algo.test(testset)
            acc.append(surprise.accuracy.rmse(predictions, verbose=True))
        A = np.mean(acc)
        KBs_mean_acc_list2.append(A)
    print("KNNBasic Done")

    KW_sim_list = ['cosine', 'pearson', 'MSD', 'pearson_baseline']
    KW_mean_acc_list2 = []

    for x in KW_sim_list:
        acc = []
        sim_options = {'name': x, 'user_based': False}
        algo = surprise.KNNWithMeans(sim_options=sim_options)

        for i, (trainset, testset) in enumerate(kf.split(data)):
            algo.fit(trainset)
            predictions = algo.test(testset)
            acc.append(surprise.accuracy.rmse(predictions, verbose=True))
        A = np.mean(acc)
        KW_mean_acc_list2.append(A)
    print("KNNWithbasic Done")

    KBl_list = [(5, 10, 5), (10, 20, 15), (20, 30, 20)]
    KBl_mean_acc_list2 = []

    for x, y, z in KBl_list:
        acc = []
        sim_options = {'name': 'pearson_baseline', 'user_based': False}
        bsl_options = {'method': 'als', 'n_epochs': x, 'reg_u': y, 'reg_i': z}
        algo = surprise.KNNBaseline(sim_options=sim_options, bsl_options=bsl_options)

        for i, (trainset, testset) in enumerate(kf.split(data)):
            algo.fit(trainset)
            predictions = algo.test(testset)
            acc.append(surprise.accuracy.rmse(predictions, verbose=True))
        A = np.mean(acc)
        KBl_mean_acc_list2.append(A)
    print("KNNBaseline Done")

    print(KBs_mean_acc_list2)
    print(KW_mean_acc_list2)
    print(KBl_mean_acc_list2)

    trainset = data.build_full_trainset()
    testset = trainset.build_anti_testset()

    # TODO: Requirement 3-4. Matrix-factorization Recommendation
    # TODO: set algorithm for 3-4-1
    algo = surprise.prediction_algorithms.matrix_factorization.SVD(n_factors=100, n_epochs=50, biased=False)
    algo.fit(trainset)
    results = get_top_n(algo, testset, uid_list, n=5, user_based=True)
    with open('3-4-1.txt', 'w') as f:
        for uid, ratings in sorted(results.items(), key=lambda x: x[0]):
            f.write('User ID %s top-5 results\n' % uid)
            for bname, score in ratings:
                f.write('Bundle NAME %s\n\tscore %s\n' % (bname, str(score)))
            f.write('\n')
    print("3-4-1 done")

    # TODO: set algorithm for 3-4-2
    algo = surprise.prediction_algorithms.matrix_factorization.SVD(n_factors=200, n_epochs=100, biased=True)
    algo.fit(trainset)
    results = get_top_n(algo, testset, uid_list, n=5, user_based=True)
    with open('3-4-2.txt', 'w') as f:
        for uid, ratings in sorted(results.items(), key=lambda x: x[0]):
            f.write('User ID %s top-5 results\n' % uid)
            for bname, score in ratings:
                f.write('Bundle NAME %s\n\tscore %s\n' % (bname, str(score)))
            f.write('\n')
    print("3-4-2 done")

    # TODO: set algorithm for 3-4-3
    algo = surprise.prediction_algorithms.matrix_factorization.SVDpp(n_factors=100, n_epochs=50)
    algo.fit(trainset)
    results = get_top_n(algo, testset, uid_list, n=5, user_based=True)
    with open('3-4-3.txt', 'w') as f:
        for uid, ratings in sorted(results.items(), key=lambda x: x[0]):
            f.write('User ID %s top-5 results\n' % uid)
            for bname, score in ratings:
                f.write('Bundle NAME %s\n\tscore %s\n' % (bname, str(score)))
            f.write('\n')
    print("3-4-3 done")

    # TODO: set algorithm for 3-4-4
    algo = surprise.prediction_algorithms.matrix_factorization.SVDpp(n_factors=100, n_epochs=100)
    algo.fit(trainset)
    results = get_top_n(algo, testset, uid_list, n=5, user_based=True)
    with open('3-4-4.txt', 'w') as f:
        for uid, ratings in sorted(results.items(), key=lambda x: x[0]):
            f.write('User ID %s top-5 results\n' % uid)
            for bname, score in ratings:
                f.write('Bundle NAME %s\n\tscore %s\n' % (bname, str(score)))
            f.write('\n')
    print("3-4-4 done")

    # TODO: 3-4-5. Best Model
    print("This is best model")
    best_algo_mf = surprise.prediction_algorithms.matrix_factorization.SVDpp(n_factors=150, n_epochs=150)
    best_algo_mf.fit(trainset)
    results = get_top_n(best_algo_mf, testset, uid_list, n=5, user_based=True)
    print(results)

    print("Cross validation...")
    np.random.seed(0)
    kf = surprise.model_selection.split.KFold(n_splits=5, random_state=0)

    SVD_sim_list = [(100, 50, True), (100, 50, False), (200, 100, True), (200, 100, False)]
    SVD_mean_acc_list = []

    for x, y, z in SVD_sim_list:
        acc = []
        algo = surprise.prediction_algorithms.matrix_factorization.SVD(n_factors=x, n_epochs=y, biased=z)

        for i, (trainset, testset) in enumerate(kf.split(data)):
            algo.fit(trainset)
            predictions = algo.test(testset)
            acc.append(surprise.accuracy.rmse(predictions, verbose=True))
        A = np.mean(acc)
        SVD_mean_acc_list.append(A)
    print("SVD Done")

    SVDpp_sim_list = [(70, 30), (100, 50), (150, 100), (150, 150)]
    SVDpp_mean_acc_list = []

    for x, y in SVDpp_sim_list:
        acc = []
        algo = surprise.prediction_algorithms.matrix_factorization.SVDpp(n_factors=x, n_epochs=y)

        for i, (trainset, testset) in enumerate(kf.split(data)):
            algo.fit(trainset)
            predictions = algo.test(testset)
            acc.append(surprise.accuracy.rmse(predictions, verbose=True))
        A = np.mean(acc)
        SVDpp_mean_acc_list.append(A)
    print("SVDpp Done")

    NMF_sim_list = [(100, 50, True), (100, 50, False), (200, 100, True), (200, 100, False)]
    NMF_mean_acc_list = []

    for x, y, z in NMF_sim_list:
        acc = []
        algo = surprise.prediction_algorithms.matrix_factorization.NMF(n_factors=x, n_epochs=y, biased=z)

        for i, (trainset, testset) in enumerate(kf.split(data)):
            algo.fit(trainset)
            predictions = algo.test(testset)
            acc.append(surprise.accuracy.rmse(predictions, verbose=True))
        A = np.mean(acc)
        NMF_mean_acc_list.append(A)
    print("NMF Done")

    print(SVD_mean_acc_list)
    print(SVDpp_mean_acc_list)
    print(NMF_mean_acc_list)


if __name__ == '__main__':
    part1()
    part2()
    part3()
