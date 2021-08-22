import random

class covid():
    def __init__(self):
        """기본 설정"""
        self.vaccine = [0.25, 0.5, 1.0]
        self.country = ['한국', '중국', '일본', '미국', '독일']
        self.pop = [1500, 3000, 2000, 2500, 2200]
        self.pop_inf = [300, 800, 500, 750, 1000]
        self.more_infect = 0 # 라운드마다 추가로 감염된 감염자 수 누적
        self.cured = 0 # 라운드마다 백신으로 치료된 감염자 수 누적
        
    def print_vaccine(self):
        """1번 메뉴 선택 시 출력되는 화면"""
        for i, rate in enumerate(self.vaccine):
            print(f'백신 이름 : 백신{i}')
            print(f'백신 치료율 : {int(100 * rate)}%')
            print('')
    
    def print_country_info(self):
        """각 나라의 감염 정보가 출력되는 화면 (완치 국가는 제외)"""
        good_count = 0
        for i, country in enumerate(self.country):
            if self.pop_inf[i] == 0: # 해당 국가 완치
                good_count += 1 # 완치 코인 적립
                continue
            else:
                print(f'감염 국가 : {country}')
                print(f'인구수 : {self.pop[i]}명')
                print(f'감염 인구수 : {self.pop_inf[i]}명')
                print('')
        
        if good_count == len(self.country): # 모든 국가가 완치인 상태..!
            print('축하합니다!!! 코로나는 정복되었습니다!!!')
            # 참고 : 이 상황은 5개국이 모두 백신3을 맞아야만 볼 수 있는 문구이다.
            # 등장 확률이.... 너무 희박하네요 ㅠ
            
    def cure(self, round_num, vac_num, country_num):
        """매 라운드 한 백신으로 한 나라가 치료되는 과정을 구현"""
        """round_num은 1~5에 해당하는 정수 (라운드 번호)"""
        """vac_num, country_num은 각각 1~3, 1~5에 해당하는 정수"""
        # 편의상 변수명 변경
        rn = round_num
        vn = vac_num
        cn = country_num
        rate = self.vaccine[vn - 1]
        country = self.country[cn - 1]
        pop = self.pop[cn - 1]
        pop_inf = self.pop_inf[cn - 1]
        
        # 선택된 백신/나라 출력
        print(f'# {rn}번째 시도 #')
        print(f'선택된 백신: 백신{vn}, 치료율: {rate * 100:4.1f}%')
        print(f'선택된 나라: {country}, 인구수: {pop}명, 감염자수: {pop_inf}명')
        
        # 백신 투여!
        cured = int(rate * self.pop_inf[cn - 1])
        self.cured += cured # 치료자 수 통계 누적
        self.pop_inf[cn - 1] -= cured # 실제 국가 감염자 수 변경
        
        # 해당 라운드 결과 보여주기
        print('=' * 40)
        if self.pop_inf[cn - 1] == 0: # 완치~
            print(f'완치된 국가: {country}')
        print(f'{rn}차 백신 투여 후 감염된 나라에 대한 정보')
        print('=' * 40)
        self.print_country_info()
        
    def infect(self):
        """감염자 증가! (모든 나라가 매 라운드 1.15배)"""
        """완치 국가이면 어차피 0 -> 0이므로 괜찮."""
        for i in range(len(self.pop_inf)):
            more = int(0.15 * self.pop_inf[i]) 
            self.more_infect += more # 추가 감염자 수 통계 누적
            self.pop_inf[i] += more # 실제 국가 감염자 수 변경
        
    def print_score(self):
        """최종 결과 출력하는 함수"""
        print('=' * 40)
        print(' ' * 15 + '최종 결과' + ' ' * 15)
        print('=' * 40)
        print(f'라운드마다 추가로 감염된 감염자 수: {self.more_infect}명')
        print(f'백신으로 치료된 감염자 수: {self.cured}명')
        print(f'백신으로 완치된 국가: ', end='')
        count = 0 # 완치 국가 개수 카운트
        for i, p in enumerate(self.pop_inf):
            if p != 0: # 미완치
                continue
            else: # 완치
                print(self.country[i], end=' ')
                count += 1
        print(f'({count}개)')
        
        # 감염자 수 많은 순서대로 정렬
        D = {}
        for i, c in enumerate(self.country):
            D[c] = self.pop_inf[i]
        
        D = sorted(D.items(), key=(lambda x: x[1]), reverse=True)
        
        rank = 1 # 감염자 수 랭킹
        for d in D:
            country = d[0]
            pop_inf = d[1]
            i = self.country.index(country) # country가 self.country 리스트에서 몇 번째 원소인지
            print(f'{rank}위')
            print(f'국가 : {country}')
            print(f'인구수 : {self.pop[i]}명')
            print(f'감염 인구수 : {pop_inf}명')
            print('')
            rank += 1
            
        print('게임 종료!')
            
def main():
    cv = covid()
    while True:
        print('-' * 30)
        print(' ' * 8 + '코로나 종식 게임' + ' ' * 8)
        print('-' * 30)
        print('1. 백신 정보')
        print('2. 감염된 국가 정보')
        print('3. 게임 시작')
        print('4. 게임 종료')
        
        N = input()
        if N == '1':
            cv.print_vaccine()
        elif N == '2':
            cv.print_country_info()
        elif N == '3':
            a = input('사용할 백신(1~3)과 백신을 적용할 국가(1~5)의 번호를 차례대로 입력하세요.\n(띄어쓰기 한 칸 필수)')
            a = a.split(' ')
            a = [int(aa) for aa in a] # 리스트 a의 각 성분을 정수로
            vac_num, country_num = a[0], a[1]
            for round_num in [1, 2, 3, 4, 5]:
                cv.cure(round_num, vac_num, country_num)
                cv.infect()
                # 만약 감염자 수 > 인구 수 라면 게임 즉시 중단 후 최종 결과 창으로 이동
                for i in range(len(cv.country)):
                    if cv.pop_inf[i] > cv.pop[i]:
                        print(f'비상! 비상! {cv.country[i]} 감염자 대폭발! 게임 중단!')
                        cv.print_score() # 최종 결과 창
                        return 0
                vac_num = random.randint(1, 3) # 1 ~ 3 중 random한 수
                country_num = random.randint(1, 5) # 1 ~ 5 중 random한 수
            cv.print_score() # 최종 결과 창
            return 0
                
        elif N == '4':
            print('게임 종료')
            return 0
        else:
            print('올바른 메뉴(1~4)를 입력하세요!')
                
        
main()