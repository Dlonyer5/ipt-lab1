from rest_framework import serializers
from .models import LibraryRecord

class LibrarySerializer(serializers.ModelSerializer):
    class Meta:
        model = LibraryRecord
        fields = '__all__'