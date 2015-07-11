
#各モンスターと技が持つタイプ
class Type
	attr_accessor :name
	def do(hp,atk,defence)
	end
end

class Gu < Type
	def initialize()
		@name = "gu"
	end
	def do(hp,atk,defence)
		p "GU"
		return hp ,atk/2 ,defence*2
	end
end

class Cho < Type
	def initialize()
		@name = "cho"
	end
	def do(hp,atk,defence)
		return hp ,atk*2 ,defence/2
	end
end

class Pa < Type
	def initialize()
		@name = "pa"
	end
	def do(hp,atk,defence)
		return hp*4 ,atk/2 ,defence/2
	end
end

#各モンスターが持つ技

class Waza
	attr_accessor :name ,:type
	def initialize(name)
		@name = name
	end

	def do(m,e)
		puts m.name.to_s + "の" + @name.to_s + "!"

		wazatype = self.type.name
		entype = e.type.name
		@state = judge(self.type.name,e.type.name)

	end
end

class Kirisaku < Waza
	def initialize()
		@name = "きりさく"
		@type = Cho.new()
	end
	def do(m,e)
		super(m,e)
		if(@state) then
			p "勝ち"
			puts "攻撃力×2!"
			e.damage(m.atk*2);
		elsif (@state==false) then
			p "負け"
			e.damage(m.atk/2);
		else
			p "あいこ"
		end
	end
end

class Knuckle < Waza
	def initialize()
		@name = "ナックルパンチ"
		@type = Gu.new()
	end
	def do(m,e)
		super(m,e)
		if(@state) then
			p "勝ち"
			puts "攻撃力×2!"
			e.damage(m.atk*2);
		elsif (@state==false) then
			p "負け"
			e.damage(m.atk/2);
		else
			p "あいこ"
		end
	end
end

class Henka < Waza
	def do(m,e)

	end
end


class Monster
	attr_accessor :name ,:hp , :atk ,:def , :type ,:type2 ,:waza1 , :status
	def initialize(name,hp,atk,defence,type)
		@name = name
		@hp = hp
		@def = defence
		@type = type
		@status = ""
	end

	def damage(hp_damage)
		damage = hp_damage-@def
		if(damage>0) then
			puts @name+"に"+damage.to_s + "のダメージ"
			if(@hp<damage)
				puts "死"
				@status = "死"
				@hp = 0
				return false
			end

			@hp -= damage
		else
			puts @name+"に0のダメージ"
		end

		return @hp
	end

	def show_status
		puts "-------"
		puts "name:"+@name
		puts "hp:"+@hp.to_s
		puts "atk:"+@atk.to_s
		puts "def:"+@def.to_s
		puts "type:"+@type.name.to_s
		puts "status:"+@status.to_s
		puts "-------"
	end
end

class Slime < Monster
	def initialize()
		@name = "スライム"
		@hp = 5
		@atk = 5
		@def = 5
		@type = Gu.new()
		@waza1 = Knuckle.new()
		@hp,@atk,@def = self.type.do(@hp,@atk,@def)
	end
end

class SlimeBes < Slime
	def initialize
		super()
		@name = "スライムベス"
		@hp ,@atk,@def= @hp.to_i*2,@atk.to_i*2,@def.to_i*2
		@type2 = Pa.new()
	end
end


class Drakee < Monster
	def initialize()
		@name = "ドラキー"
		@hp = 4
		@atk = 6
		@def =5
		@type = Cho.new()
		@waza1 = Kirisaku.new()
	end
end

class Nyan < Monster
	def initialize
		@name = "プリズニャン"
		@hp = 10
		@atk = 3
		@def = 2
		@type = Pa.new()
	end
end

def judge(j1,j2)
	if(j1==j2)then
		return nil
	elsif(j1=="gu") then
		return j2=="cho"
	elsif(j1=="cho") then
		return j2=="pa"
	elsif(j1=="pa")then
		return j2=="gu"
	end
end

# m = Monster.new("slime",10,10,10,"cho")
s = Slime.new()
d = Drakee.new()
b = SlimeBes.new()
p = Nyan.new()

d.show_status
s.show_status
d.waza1.do(d,s)
s.waza1.do(s,d)
d.show_status
s.show_status
