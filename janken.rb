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

class Monster
	attr_accessor :name ,:hp , :atk ,:def , :type ,:type2
	def initialize(name,hp,atk,defence,type)
		@name = name
		@hp = hp
		@atk = atk
		@def = defence
		@type = type
	end

	def damage(hp_damage)
		@hp -= hp_damage-@def
		puts @name+"に"+(hp_damage-@def).to_s + "のダメージ"
		if(@hp<=0)
			puts "死"
			return false
		end
		return @hp
	end

	def type_ability
		@hp,@atk,@def = @type.do(@hp,@atk,@def)
	end

	def type2_ability
		@hp,@atk,@def = @type2.do(@hp,@atk,@def)
	end

	def show_status
		puts "-------"
		puts "name:"+@name
		puts "hp:"+@hp.to_s
		puts "atk:"+@atk.to_s
		puts "def:"+@def.to_s
		puts "type:"+@type.name.to_s
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
		type_ability()
	end
end

class SlimeBes < Slime
	def initialize
		super()
		@name = "スライムベス"
		@hp ,@atk,@def= @hp.to_i*2,@atk.to_i*2,@def.to_i*2
		@type2 = Pa.new()
		type2_ability
	end
end


class Drakee < Monster
	def initialize()
		@name = "ドラキー"
		@hp = 4
		@atk = 6
		@def =5
		@type = Cho.new()
		type_ability()
	end
end

class Nyan < Monster
	def initialize
		@name = "プリズニャン"
		@hp = 10
		@atk = 3
		@def = 2
		@type = Pa.new()
		type_ability
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

def janken(m1,m2)
	if(judge(m1.type.name,m2.type.name))then
		puts m1.name.to_s + "の勝ち"
		m2.damage(m1.atk)
	elsif (judge(m1.type.name,m2.type.name)==false)then
		puts m2.name.to_s + "の勝ち"
		m1.damage(m2.atk)
	else 
		puts "あいこ！"
	end
end

# m = Monster.new("slime",10,10,10,"cho")
s = Slime.new()
d = Drakee.new()
b = SlimeBes.new()
p = Nyan.new()

p b.show_status

s.show_status
d.show_status

janken(s,d)

janken(s,b)

s.show_status()
d.show_status()
