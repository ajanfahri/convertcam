<?php

class GCode{

  private $conn;
  private $table_name = "gcodes";
    
  private $baslik;
  private $aciklama;
  private $rows;
  private $yuklenme_tarihi;
  private $kayit_tarihi;
  private $yayin_tarihi;
  private $result=array();

  public function __construct($db){
    $this->conn=$db;
  }
  
        function tumunuGetir(){
          $query = "SELECT * FROM " . $this->table_name;
          $stmt = $this->conn->prepare($query);
          $stmt->execute();
          return $stmt->fetchAll();
        }

        function adetGetir($from){
          $query = "SELECT * FROM " . $this->table_name ." order by kayit_tarihi DESC LIMIT ".$from.",20";
          $stmt = $this->conn->prepare($query);
          $stmt->execute();
          $sonuc = new \stdClass();
          $sonuc->toplam = $stmt->rowCount();
          $sonuc->baslangic = $from;
          $sonuc->bitis = $from+$stmt->rowCount();
          $sonuc->sonuclar = $stmt->fetchAll();
          return $sonuc;
        }
        

        
        function toplamKayit(){
          $query = "SELECT * FROM " . $this->table_name;
          $stmt = $this->conn->prepare($query);
          $stmt->execute();
          return $stmt->rowCount();
        } 
}



?>